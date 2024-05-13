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
class SceneManager;

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

    Game() noexcept(false);
    ~Game() = default;

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
    SceneManager* m_sceneManager;

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
