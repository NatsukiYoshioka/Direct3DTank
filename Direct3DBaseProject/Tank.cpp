#include<string>
#include "pch.h"
#include"Game.h"
#include"Bullet.h"
#include"common.h"
#include "Tank.h"

const string Tank::m_tankBonesName = "tank_geo";
const string Tank::m_leftBackWheelName = "l_back_wheel_geo";
const string Tank::m_rightBackWheelName = "r_back_wheel_geo";
const string Tank::m_leftFrontWheelName = "l_front_wheel_geo";
const string Tank::m_rightFrontWheelName = "r_front_wheel_geo";
const string Tank::m_turretName = "turret_geo";
const string Tank::m_canonName = "canon_geo";
const string Tank::m_hatchName = "hatch_geo";

extern void ExitGame() noexcept;

//タンクの初期化
Tank::Tank(unique_ptr<DirectX::Model>&& tankModelHandle, DirectX::Model *bulletModelHandle, Vector3 pos, float angle) :
    m_tankModelHandle(move(tankModelHandle)),
    m_direction(),
    m_pos(pos),
    m_world(),
    m_local(),
    m_hitLocal(),
    m_angle(angle),
    m_fireRecast(static_cast<float>(initializeNum)),
    m_isMove(false),
    m_isMoveLeft(false),
    m_isMoveRight(false),
    m_isFire(false),
    m_isHitBlock(false),
    m_turretRotation(angle),
    m_leftBackWheelBone(ModelBone::c_Invalid),
    m_rightBackWheelBone(ModelBone::c_Invalid),
    m_leftFrontWheelBone(ModelBone::c_Invalid),
    m_rightFrontWheelBone(ModelBone::c_Invalid),
    m_turretBone(ModelBone::c_Invalid),
    m_canonBone(ModelBone::c_Invalid),
    m_hatchBone(ModelBone::c_Invalid)
{
    m_bulletModelHandle = bulletModelHandle;

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

//タンクの更新処理
void Tank::Update(DirectX::SimpleMath::Matrix world, DirectX::GamePad::State padState)
{
    UpdateInput(padState);
    UpdateAnimation();
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
void Tank::Draw(ID3D11DeviceContext1* deviceContext, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    auto context = deviceContext;

    size_t nbones = m_tankModelHandle->bones.size();

    m_tankModelHandle->CopyAbsoluteBoneTransforms(nbones, m_animBones.get(), m_drawBones.get());

    m_tankModelHandle->Draw(context, *states, nbones, m_drawBones.get(), m_local, view, projection);

    if (m_bullets.size() > initializeNum)
    {
        for (int i = initializeNum; i < m_bullets.size(); i++)
        {
            m_bullets.at(i)->Draw(deviceContext, move(states), view, projection);
        }
    }
}

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
        if (padState.IsRightShoulderPressed() && m_fireRecast == static_cast<float>(initializeNum))
        {
            m_isFire = true;
        }

        m_direction.x = padState.thumbSticks.leftX;
        m_direction.y = padState.thumbSticks.leftY;
        m_direction.Normalize();
        m_pos.z += m_direction.x * m_speed;
        m_pos.x += m_direction.y * m_speed;
    }
}

//アニメーション更新
void Tank::UpdateAnimation()
{
    float wheelRotation = Game::GetTime() * m_wheelRotationSpeed;
    XMMATRIX mat;
    if (m_isMove)
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
}

//弾の更新
void Tank::UpdateBullets(DirectX::SimpleMath::Matrix world)
{
    //リキャスト計算
    if (m_fireRecast > static_cast<float>(initializeNum))
    {
        m_fireRecast -= m_recastSpeed;
    }
    if (m_fireRecast < static_cast<float>(initializeNum))
    {
        m_fireRecast = static_cast<float>(initializeNum);
        m_isFire = false;
    }
}

//ブロックとの当たり判定
void Tank::CheckHitBlock(BoundingBox blockBox, Vector3 blockPos)
{
    m_isHitBlock = m_tankModelHandle->meshes.at(initializeNum)->boundingBox.Intersects(blockBox);
    if (m_isHitBlock)
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