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
    m_local(),
    m_angle(angle),
    isMove(false),
    isMoveLeft(false),
    isMoveRight(false),
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
    //座標処理
    world = XMMatrixMultiply(world, Matrix::CreateScale(m_scale));
    world = XMMatrixMultiply(world, Matrix::CreateRotationY(m_angle));
    m_local = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
    m_local = XMMatrixMultiply(world, m_local);
}

//タンクの描画処理
void Tank::Draw(ID3D11DeviceContext1* deviceContext, unique_ptr<DirectX::CommonStates>&& states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
    auto context = deviceContext;

    size_t nbones = m_tankModelHandle->bones.size();

    m_tankModelHandle->CopyAbsoluteBoneTransforms(nbones, m_animBones.get(), m_drawBones.get());

    m_tankModelHandle->Draw(context, *states, nbones, m_drawBones.get(), m_local, view, projection);
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
            isMove = true;
        }
        else isMove = false;
        
        //右スティックの入力状態
        if (padState.thumbSticks.rightX > static_cast<float>(initializeNum))
        {
            isMoveRight = true;
            isMoveLeft = false;
        }
        else if (padState.thumbSticks.rightX < static_cast<float>(initializeNum))
        {
            isMoveRight = false;
            isMoveLeft = true;
        }
        else
        {
            isMoveRight = false;
            isMoveLeft = false;
        }
        if (padState.IsRightTriggerPressed())
        {

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
    if (isMove)
    {
        //ホイールのアニメーション
        mat = XMMatrixRotationX(wheelRotation);
        m_animBones[m_leftFrontWheelBone] = XMMatrixMultiply(mat, m_tankModelHandle->boneMatrices[m_leftFrontWheelBone]);
        m_animBones[m_rightFrontWheelBone] = XMMatrixMultiply(mat, m_tankModelHandle->boneMatrices[m_rightFrontWheelBone]);
        m_animBones[m_leftBackWheelBone] = XMMatrixMultiply(mat, m_tankModelHandle->boneMatrices[m_leftBackWheelBone]);
        m_animBones[m_rightBackWheelBone] = XMMatrixMultiply(mat, m_tankModelHandle->boneMatrices[m_rightBackWheelBone]);
    }
    //タレットのアニメーション
    if (isMoveRight)
    {
        m_turretRotation -= m_turretRotationSpeed;
    }
    if (isMoveLeft)
    {
        m_turretRotation += m_turretRotationSpeed;
    }
    mat = XMMatrixMultiply(XMMatrixRotationY(m_turretRotation), Matrix::CreateRotationY(-m_angle));
    m_animBones[m_turretBone] = XMMatrixMultiply(mat, m_tankModelHandle->boneMatrices[m_turretBone]);
}