#pragma once

using namespace DirectX;
using namespace std;

class SceneManager;
class TankManager;
class BulletManager;
class BlockManager;

class SoundManager
{
public:
	SoundManager(vector<string> soundfile, AudioEngine* audioEngine);
	~SoundManager();

	void Init();
	void Update(SceneManager* sceneManager, DirectX::GamePad::State padState, TankManager* tankManager, BulletManager* bulletManager, BlockManager* blockManager);

	bool m_isMoveStickRight;
	bool m_isMoveStickLeft;
private:
	vector<unique_ptr<SoundEffect>> m_sound;
	vector<unique_ptr<SoundEffectInstance>> m_loopSound;
	vector<bool> m_isPlaySound;
	vector<bool> m_isPlayBreakBlockSound;

	static constexpr float m_BGMVolume = 0.25f;

	vector<int> m_fireSoundCount;
};

