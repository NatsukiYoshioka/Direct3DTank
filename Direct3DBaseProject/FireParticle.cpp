#include "pch.h"
#include<random>
#define _USE_MATH_DEFINES
#include<math.h>
#include"common.h"
#include "FireParticle.h"

//����G�t�F�N�g�p�[�e�B�N���̒ǉ�
FireParticle::FireParticle(Vector3 pos):
    m_pos(pos),
    m_firstHeight(pos.y+m_sponeHeight),
    m_isFinish(false)
{
    m_pos.y = m_firstHeight;
    //�����オ��ő�Y���ʂ̐ݒ�
    std::random_device random;
    std::mt19937 generator(random());
    using dist_type = std::uniform_real_distribution<float>;
    dist_type distribution(m_minDistributionUpVectorY, m_maxDistributionUpVectorY);
    m_maxUpVectorY = m_pos.y + distribution(generator);

    //���̏㏸�X�s�[�h�ݒ�
    dist_type::param_type param(m_minUpSpeed, m_maxUpSpeed);
    distribution.param(param);
    m_upSpeed = distribution(generator);

    //�����オ��ꏊ�̐ݒ�
    param._Min = m_minDirection;
    param._Max = m_maxDirection;
    distribution.param(param);
    float degree = distribution(generator) * 180.f / M_PI;
    float cos, sin;
    cos = std::cos(degree);
    sin = std::sin(degree);
    m_direction.x = sin;
    m_direction.z = cos;

    param._Min = m_minWidth;
    param._Max = m_maxWidth;
    distribution.param(param);
    float widthX = distribution(generator);
    float widthZ = distribution(generator);
    m_direction.x *= widthX;
    m_direction.z *= widthZ;
}

//�f�[�^���
FireParticle::~FireParticle()
{

}

//�p�[�e�B�N���X�V
void FireParticle::Update()
{
    m_pos += m_direction;
    m_pos.y += m_upSpeed;

    //�ڕWY���W�ɒB������p�[�e�B�N���X�V�I��
    if (m_pos.y >= m_maxUpVectorY)
    {
        m_isFinish = true;
    }
}

//�p�[�e�B�N���`��
void FireParticle::Draw(ID3D11DeviceContext1* context, DirectX::CommonStates* states, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch, BasicEffect* basicEffect, ID3D11InputLayout* inputLayout)
{
    auto Context = context;
    //��Z�Ȃ��̓��߂ɐݒ�
    Context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);
    Context->OMSetDepthStencilState(states->DepthRead(), initializeNum);
    Context->RSSetState(states->CullNone());

    //�F�A���ߓx�̐ݒ�
    basicEffect->SetDiffuseColor(Vector3(1.f - (m_pos.y - m_firstHeight) / (m_maxDistributionUpVectorY + m_firstHeight), 0.f, 0.f));
    basicEffect->SetAlpha(1.f - m_pos.y / (m_maxDistributionUpVectorY + m_firstHeight));
    basicEffect->Apply(Context);

    auto sampler = states->LinearClamp();
    Context->PSSetSamplers(0, 1, &sampler);

    Context->IASetInputLayout(inputLayout);

    //�J�����ʒu�A����p�̎擾
    basicEffect->SetView(view);
    basicEffect->SetProjection(projection);

    //�e�N�X�`���p�̃r���{�[�h�ݒ�
    VertexPositionTexture v1(Vector3(m_pos.x, m_pos.y + m_textureWidth, m_pos.z - m_textureWidth), Vector2(0.f, 0.f));
    VertexPositionTexture v2(Vector3(m_pos.x, m_pos.y + m_textureWidth, m_pos.z + m_textureWidth), Vector2(1.f, 0.f));
    VertexPositionTexture v3(Vector3(m_pos.x, m_pos.y - m_textureWidth, m_pos.z + m_textureWidth), Vector2(1.f, 1.f));
    VertexPositionTexture v4(Vector3(m_pos.x, m_pos.y - m_textureWidth, m_pos.z - m_textureWidth), Vector2(0.f, 1.f));

    //�`��
    primitiveBatch->Begin();
    primitiveBatch->DrawQuad(v1, v2, v3, v4);
    primitiveBatch->End();
}