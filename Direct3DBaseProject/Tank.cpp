#define NOMINMAX
#include<string>
#include "pch.h"
#include"Game.h"
#include"Bullet.h"
#include"SceneManager.h"
#include"common.h"
#include"Load.h"
#include "Tank.h"

const string Tank::m_tankBonesName = "tank_geo";
const string Tank::m_leftBackWheelName = "l_back_wheel_geo";
const string Tank::m_rightBackWheelName = "r_back_wheel_geo";
const string Tank::m_leftFrontWheelName = "l_front_wheel_geo";
const string Tank::m_rightFrontWheelName = "r_front_wheel_geo";
const string Tank::m_turretName = "turret_geo";
const string Tank::m_canonName = "canon_geo";
const string Tank::m_hatchName = "hatch_geo";

const Vector2 Tank::m_resultLookAt(1.f, 12.f);

extern void ExitGame() noexcept;

//タンクの初期化
Tank::Tank(unique_ptr<DirectX::Model>&& tankModelHandle, Vector3 pos, float angle) :
    m_hp(maxHp),
    m_tankModelHandle(move(tankModelHandle)),
    m_direction(),
    m_initMainGamePos(pos),
    m_pos(),
    m_world(),
    m_local(),
    m_hitLocal(),
    m_initMainGameAngle(angle),
    m_angle(),
    m_fireRecast(static_cast<float>(initializeNum)),
    m_isMove(false),
    m_isMoveLeft(false),
    m_isMoveRight(false),
    m_isFire(false),
    m_isHitBlockOrTank(false),
    m_isHitBullet(false),
    m_isBreak(false),
    m_turretRotation(),
    m_leftBackWheelBone(ModelBone::c_Invalid),
    m_rightBackWheelBone(ModelBone::c_Invalid),
    m_leftFrontWheelBone(ModelBone::c_Invalid),
    m_rightFrontWheelBone(ModelBone::c_Invalid),
    m_turretBone(ModelBone::c_Invalid),
    m_canonBone(ModelBone::c_Invalid),
    m_hatchBone(ModelBone::c_Invalid)
{
    const size_t nbones = m_tankModelHandle->bones.size();

    //ボーン配列の生成
    m_drawBones = ModelBone::MakeArray(nbones);
    m_animBones = ModelBone::MakeArray(nbones);

    //ボーンの検索
    uint32_t index = initializeNum;
    for (const auto& it : m_tankModelHandle->bones)
    {
        if (_wcsicmp(it.name.c_str(), Widen(m_tankBonesName).c_str()) == initializeNum)
        {
            m_animBones[index] = XMMatrixIdentity();
        }
        else if (_wcsicmp(it.name.c_str(), Widen(m_leftBackWheelName).c_str()) == initializeNum) { m_leftBackWheelBone = index; }
        else if (_wcsicmp(it.name.c_str(), Widen(m_rightBackWheelName).c_str()) == initializeNum) { m_rightBackWheelBone = index; }
        else if (_wcsicmp(it.name.c_str(), Widen(m_leftFrontWheelName).c_str()) == initializeNum){ m_leftFrontWheelBone = index; }
        else if (_wcsicmp(it.name.c_str(), Widen(m_rightFrontWheelName).c_str()) == initializeNum) { m_rightFrontWheelBone = index; }
        else if (_wcsicmp(it.name.c_str(), Widen(m_turretName).c_str()) == initializeNum) { m_turretBone = index; }
        else if (_wcsicmp(it.name.c_str(), Widen(m_canonName).c_str()) == initializeNum) { m_canonBone = index; }
        else if (_wcsicmp(it.name.c_str(), Widen(m_hatchName).c_str()) == initializeNum) { m_hatchBone = index; }
        ++index;
    }

    m_tankModelHandle->CopyBoneTransformsTo(nbones, m_animBones.get());

    m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Extents.x = m_boundingboxExtents;
    m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Extents.y = m_boundingboxExtents;
    m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Extents.z = m_boundingboxExtents;
}

//インスタンス破棄
Tank::~Tank()
{
    m_tankModelHandle.reset();
}

//タイトル時の初期化
void Tank::InitTitle(Vector3 pos, float angle)
{
    m_pos = pos;
    m_angle = angle;
    m_turretRotation = angle;

    m_hp = maxHp;
    m_isBreak = false;
}

//メインゲーム時の初期化
void Tank::InitMainGame()
{
    m_pos = m_initMainGamePos;
    m_angle = m_initMainGameAngle;
    m_turretRotation = m_initMainGameAngle;

    m_fireRecast = static_cast<float>(initializeNum);
}

//リザルト時の初期化
void Tank::InitResult(Vector3 pos, Vector3 cameraEye)
{
    m_isMove = false;
    m_isMoveLeft = false;
    m_isMoveRight = false;
    m_isFire = false;

    m_pos = pos;
    m_angle = atan2f(m_resultLookAt.x - m_pos.x, m_resultLookAt.y - m_pos.z);
    m_turretRotation = atan2f(cameraEye.x - m_pos.x, cameraEye.z - m_pos.z);
}

//タンクの更新処理
void Tank::Update(DirectX::SimpleMath::Matrix world, DirectX::GamePad::State padState, SceneManager::SCENE sceneState)
{
    if (sceneState == SceneManager::SCENE::MAINGAME)
    {
        UpdateInput(padState);
    }
    UpdateAnimation(sceneState);
    UpdateBullets(world);
    //座標処理
    m_world = world;

    m_world = XMMatrixMultiply(world, Matrix::CreateScale(m_scale));
    m_world = XMMatrixMultiply(m_world, Matrix::CreateRotationY(m_angle));
    m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_local = XMMatrixMultiply(m_world, m_local);
    m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Center.x = m_pos.x;
    m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Center.y = m_pos.y;
    m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Center.z = m_pos.z;
}

//タンクの描画処理
void Tank::Draw(ID3D11DeviceContext1* deviceContext, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    auto context = deviceContext;

    size_t nbones = m_tankModelHandle->bones.size();

    m_tankModelHandle->CopyAbsoluteBoneTransforms(nbones, m_animBones.get(), m_drawBones.get());

    m_tankModelHandle->Draw(context, *states, nbones, m_drawBones.get(), m_local, view, projection);
}

//タンクを別のテクスチャで描画
void Tank::DrawFromTexture(ID3D11DeviceContext1* deviceContext, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, ID3D11ShaderResourceView* tankTexture, ID3D11ShaderResourceView* engineTexture)
{
    auto context = deviceContext;

    size_t nbones = m_tankModelHandle->bones.size();

    m_tankModelHandle->CopyAbsoluteBoneTransforms(nbones, m_animBones.get(), m_drawBones.get());

    m_tankModelHandle->Draw(context, *states, nbones, m_drawBones.get(), m_local, view, projection, false, [&]
        {
            context->PSSetShaderResources(initializeNum, m_shaderNumVeiw, &tankTexture);
            context->PSSetShaderResources(initializeNum, m_shaderNumVeiw, &engineTexture);
        });
}

//入力処理更新
void Tank::UpdateInput(DirectX::GamePad::State padState)
{
    if (padState.IsConnected())
    {
        if (padState.IsViewPressed())
        {
            ExitGame();
        }
        //左スティックの入力状態
        if (padState.thumbSticks.leftX != static_cast<float>(initializeNum) || padState.thumbSticks.leftY != static_cast<float>(initializeNum))
        {
            m_angle = atan2f(padState.thumbSticks.leftY, padState.thumbSticks.leftX);
            m_isMove = true;
        }
        else m_isMove = false;
        
        //右スティックの入力状態
        if (padState.thumbSticks.rightX > static_cast<float>(initializeNum))
        {
            m_isMoveRight = true;
            m_isMoveLeft = false;
        }
        else if (padState.thumbSticks.rightX < static_cast<float>(initializeNum))
        {
            m_isMoveRight = false;
            m_isMoveLeft = true;
        }
        else
        {
            m_isMoveRight = false;
            m_isMoveLeft = false;
        }
        if (padState.IsRightShoulderPressed() && m_fireRecast <= static_cast<float>(initializeNum))
        {
            m_fireRecast = m_maxFireRecast;
            m_isFire = true;
        }
        else m_isFire = false;

        m_direction.x = padState.thumbSticks.leftX;
        m_direction.y = padState.thumbSticks.leftY;
        m_direction.Normalize();
        m_pos.z += m_direction.x * m_speed;
        m_pos.x += m_direction.y * m_speed;
    }
}

//アニメーション更新
void Tank::UpdateAnimation(SceneManager::SCENE sceneState)
{
    float wheelRotation = Game::GetTime() * m_wheelRotationSpeed;
    //float hatchRotation = min(0.f, max(sinf(Game::GetTime() * 4.f) * 2.f, -1.f));
    XMMATRIX mat;
    if (m_isMove || sceneState == SceneManager::SCENE::TITLE)
    {
        //ホイールのアニメーション
        mat = XMMatrixRotationX(wheelRotation);
        m_animBones[m_leftFrontWheelBone] = XMMatrixMultiply(mat, m_tankModelHandle->boneMatrices[m_leftFrontWheelBone]);
        m_animBones[m_rightFrontWheelBone] = XMMatrixMultiply(mat, m_tankModelHandle->boneMatrices[m_rightFrontWheelBone]);
        m_animBones[m_leftBackWheelBone] = XMMatrixMultiply(mat, m_tankModelHandle->boneMatrices[m_leftBackWheelBone]);
        m_animBones[m_rightBackWheelBone] = XMMatrixMultiply(mat, m_tankModelHandle->boneMatrices[m_rightBackWheelBone]);
    }
    //タレットのアニメーション
    if (m_isMoveRight)
    {
        m_turretRotation -= m_turretRotationSpeed;
    }
    if (m_isMoveLeft)
    {
        m_turretRotation += m_turretRotationSpeed;
    }
    mat = XMMatrixMultiply(XMMatrixRotationY(m_turretRotation), Matrix::CreateRotationY(-m_angle));
    m_animBones[m_turretBone] = XMMatrixMultiply(mat, m_tankModelHandle->boneMatrices[m_turretBone]);

    if (sceneState == SceneManager::SCENE::RESULT)
    {
        if (!m_hp)
        {
            mat = XMMatrixRotationX(m_canonRotation);
        }
        else
        {
            mat = XMMatrixRotationX(-m_canonRotation);
            //m_animBones[m_hatchBone] = XMMatrixMultiply(XMMatrixRotationX(hatchRotation), m_tankModelHandle->boneMatrices[m_hatchBone]);
        }
    }
    else
    {
        mat = XMMatrixRotationX(static_cast<float>(initializeNum));
    }
    m_animBones[m_canonBone] = XMMatrixMultiply(mat, m_tankModelHandle->boneMatrices[m_canonBone]);
}

//弾の更新
void Tank::UpdateBullets(DirectX::SimpleMath::Matrix world)
{
    //リキャスト計算
    if (m_fireRecast > static_cast<float>(initializeNum))
    {
        m_fireRecast -= m_recastSpeed;
    }
    if (m_fireRecast <= static_cast<float>(initializeNum))
    {
        m_fireRecast = static_cast<float>(initializeNum);
    }
}

//ブロックとの当たり判定
void Tank::CheckHitBlockTank(BoundingBox blockBox, Vector3 blockPos)
{
    m_isHitBlockOrTank = m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Intersects(blockBox);
    if (m_isHitBlockOrTank)
    {
        Vector2 distance;
        distance.x = m_pos.x - blockPos.x;
        distance.y = m_pos.z - blockPos.z;
        if (distance.x < initializeNum)distance.x = -distance.x;
        if (distance.y < initializeNum)distance.y = -distance.y;
        
        if (distance.x > distance.y)
        {
            if (blockPos.x + blockBox.Extents.x - (m_pos.x - m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Extents.x) < m_pos.x + m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Extents.x - (blockPos.x - blockBox.Extents.x))
            {
                m_pos.x += blockPos.x + blockBox.Extents.x - (m_pos.x - m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Extents.x);
            }
            else
            {
                m_pos.x -= m_pos.x + m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Extents.x - (blockPos.x - blockBox.Extents.x);
            }
        }
        else if(distance.x < distance.y)
        {
            if (blockPos.z + blockBox.Extents.z - (m_pos.z - m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Extents.z) < m_pos.z + m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Extents.z - (blockPos.z - blockBox.Extents.z))
            {
                m_pos.z += blockPos.z + blockBox.Extents.z - (m_pos.z - m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Extents.z);
            }
            else
            {
                m_pos.z -= m_pos.z + m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Extents.z - (blockPos.z - blockBox.Extents.z);
            }
        }

        m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
        m_local = XMMatrixMultiply(m_world, m_local);
        m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Center.x = m_pos.x;
        m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Center.y = m_pos.y;
        m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Center.z = m_pos.z;
    }
}

//弾と戦車との当たり判定
bool Tank::CheckHitBullet(BoundingBox bulletBox, Vector3 bulletPos)
{
    m_isHitBullet = m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Intersects(bulletBox);
    if (m_isHitBullet)
    {
        m_hp--;
        if (m_hp <= initializeNum)
        {
            m_isBreak = true;
        }
    }
    return m_isHitBullet;
}