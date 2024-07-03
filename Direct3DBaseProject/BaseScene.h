#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

class TankManager;

/// <summary>
/// シーンの基底クラス
/// </summary>
class BaseScene
{
public:
	virtual void Update(DirectX::GamePad::State,TankManager* tankManager) = 0;
	virtual void Draw(DirectX::SpriteFont* defaultfont, DirectX::SpriteBatch* spriteBatch, ID3D11DeviceContext1* context = nullptr, DirectX::CommonStates* states = nullptr, DirectX::SimpleMath::Matrix view = Matrix::Identity, DirectX::SimpleMath::Matrix projection = Matrix::Identity, DirectX::PrimitiveBatch<VertexPositionTexture>* primitiveBatch = nullptr, BasicEffect* basicEffect = nullptr, Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout = nullptr, ID3D11Device* deviceResources = nullptr) = 0;
	virtual bool GetIsFinish() = 0;
};

