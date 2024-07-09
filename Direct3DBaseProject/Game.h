//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include"CommonStates.h"
#include"common.h"

class Load;
class BlockManager;
class TankManager;
class BulletManager;
class ParticleManager;
class SceneManager;
class SoundManager;
class Transition;

using namespace DirectX::SimpleMath;

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game();

    Game(Game&&) = default;
    Game& operator= (Game&&) = default;

    Game(Game const&) = delete;
    Game& operator= (Game const&) = delete;

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    void OnDeviceLost() override;
    void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnDisplayChange();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const noexcept;

    /// <summary>
    /// ŽžŠÔ‚ÌŽæ“¾
    /// </summary>
    /// <returns></returns>
    static float GetTime() { return m_time; }

private:
    Load* m_load;
    BlockManager* m_blockManager;
    TankManager* m_tankManager;
    BulletManager* m_bulletManager;
    ParticleManager* m_particleManager;
    SceneManager* m_sceneManager;
    SoundManager* m_soundManager;
    Transition* m_transition;

    unique_ptr<DirectX::GamePad> m_gamePad;

    static constexpr Vector3 m_titleCameraEye = { 0.f, 2.f, 15.0f };
    static constexpr Vector3 m_mainGameCameraEye = { 7.5f, 25.f, 7.5f };
    static const Vector3 m_resultCameraEye;

    std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
    using VertexType = DirectX::VertexPositionTexture;
    std::unique_ptr<DirectX::PrimitiveBatch<VertexType>> m_primitiveBatch;
    std::unique_ptr<DirectX::AudioEngine> m_audioEngine;

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;
    static float m_time;

    DirectX::SimpleMath::Matrix m_world;
    DirectX::SimpleMath::Matrix m_view;
    DirectX::SimpleMath::Matrix m_proj;
};
