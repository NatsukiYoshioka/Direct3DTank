//
// Game.cpp
//

#include "pch.h"
#include"Load.h"
#include"BlockManager.h"
#include"TankManager.h"
#include"BulletManager.h"
#include"ParticleManager.h"
#include"SceneManager.h"
#include "Game.h"

extern void ExitGame() noexcept;

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

float Game::m_time = static_cast<float>(initializeNum);
const Vector3 Game::m_resultCameraEye = Vector3(1.f, 1.5f, 14.0f);

Game::Game() noexcept(false):
    m_load(nullptr),
    m_blockManager(nullptr),
    m_tankManager(nullptr),
    m_bulletManager(nullptr),
    m_particleManager(nullptr),
    m_sceneManager(nullptr)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    // TODO: Provide parameters for swapchain format, depth/stencil format, and backbuffer count.
    //   Add DX::DeviceResources::c_AllowTearing to opt-in to variable rate displays.
    //   Add DX::DeviceResources::c_EnableHDR for HDR10 display.
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());
    m_time = float(timer.GetTotalSeconds());

    // TODO: Add your game logic here.
    m_blockManager->Update(m_world);
    m_tankManager->Update(m_world, m_blockManager, m_bulletManager, m_sceneManager->GetNowSceneState());
    m_bulletManager->Update(m_world, m_tankManager, m_blockManager);
    m_particleManager->Update(m_world, m_blockManager, m_tankManager, m_sceneManager);
    m_sceneManager->Update(m_tankManager);
    if (m_sceneManager->GetIsChange())
    {
        CreateWindowSizeDependentResources();
        switch (m_sceneManager->GetNowSceneState())
        {
        case SceneManager::SCENE::TITLE:
            m_blockManager->Init();
            m_particleManager->Init();
            m_tankManager->InitTitle();
            break;
        case SceneManager::SCENE::MAINGAME:
            m_tankManager->InitMainGame();
            break;
        case SceneManager::SCENE::RESULT:
            m_tankManager->InitResult(m_resultCameraEye);
            break;
        }
    }
    elapsedTime;
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    m_spriteBatch->Begin(SpriteSortMode_FrontToBack, m_load->GetStates()->NonPremultiplied());
    m_blockManager->Draw(context, m_load->GetStates(), m_view, m_proj);
    m_tankManager->Draw(context, m_load->GetStates(), m_view, m_proj, m_load->GetTankTexture(), m_load->GetEngineTexture());
    m_bulletManager->Draw(context, m_load->GetStates(), m_view, m_proj);
    m_particleManager->Draw(context, m_load->GetStates(), m_view, m_proj, m_primitiveBatch.get(), m_sceneManager);
    m_sceneManager->Draw(m_spriteBatch.get());
    m_spriteBatch->End();
    context;

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto const viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
    m_gamePad->Suspend();
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
    m_gamePad->Resume();
}

void Game::OnWindowMoved()
{
    auto const r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnDisplayChange()
{
    m_deviceResources->UpdateColorSpace();
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const noexcept
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Initialize device dependent objects here (independent of window size).
    //オブジェクトのロード
    m_spriteBatch = std::make_unique<SpriteBatch>(context);
    m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexType>>(context);

    Load::CreateInstance();
    m_load = Load::GetInstance();
    m_load->ReadFile();
    m_load->LoadData(device, context);

    m_gamePad = make_unique<GamePad>();

    SceneManager::CreateInstance(m_gamePad.get(), m_load->GetDefaultFont(), m_load->GetTitleUI(), m_load->GetTitleUIPos(), m_load->GetTitleUIScale(), m_load->GetMainGameUI(), m_load->GetMainGameUIPos(), m_load->GetMainGameUIScale(), m_load->GetResultUI(), m_load->GetResultUIPos(), m_load->GetResultUIScale());

    m_sceneManager = SceneManager::GetInstance();

    m_particleManager = new ParticleManager(m_load->GetWoodParticleModelHandle(), m_load->GetFireParticle(), move(m_load->GetFireBasicEffect()), m_load->GetFireInputLayout());

    m_blockManager = new BlockManager(move(m_load->GetBlockModelHandle()), move(m_load->GetGroundBlockUnderWoodsModelHandle()), m_load->GetMap());

    m_tankManager = new TankManager(move(m_load->GetTankModelHandle()), m_load->GetTankPos(), m_gamePad.get());

    m_bulletManager = new BulletManager(move(m_load->GetBulletModelHandle()));

    m_world = Matrix::Identity;
    device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
    auto size = m_deviceResources->GetOutputSize();
    switch (m_sceneManager->GetNowSceneState())
    {
    case SceneManager::SCENE::TITLE:
        m_view = Matrix::CreateLookAt(Vector3(0.f, 2.f, 15.0f),
            Vector3(7.5f, 0.f, 7.5f), Vector3::UnitY);
        m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
            float(size.right) / float(size.bottom), 0.1f, 500.f);
        break;
    case SceneManager::SCENE::MAINGAME:
        m_view = Matrix::CreateLookAt(Vector3(7.5f, 25.f, 7.5f),
            Vector3(7.5f, 0.f, 7.5f), Vector3::UnitX);
        m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
            float(size.right) / float(size.bottom), 0.1f, 500.f);
        break;
    case SceneManager::SCENE::RESULT:
        m_view = Matrix::CreateLookAt(m_resultCameraEye,
            Vector3(7.5f, 0.f, 7.5f), Vector3::UnitY);
        m_proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
            float(size.right) / float(size.bottom), 0.1f, 500.f);
        break;
    }
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
    Load::DestroyInstance();
    SceneManager::DestroyInstance();
    delete(m_blockManager);
    delete(m_tankManager);
    delete(m_bulletManager);
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
