#pragma once
#include"pch.h"
#include <stdexcept>
#include <SpriteBatch.h>

#include <wrl/client.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

class AnimatedTexture
{
public:
    AnimatedTexture() noexcept :
        mPaused(false),
        mFrame(0),
        mSideFrameCount(0),
        mWarpFrameCount(0),
        mTextureWidth(0),
        mTextureHeight(0),
        mTimePerFrame(0.f),
        mTotalElapsed(0.f),
        mDepth(0.f),
        mRotation(0.f),
        mOrigin{},
        mScale(1.f, 1.f)
    {
    }

    AnimatedTexture(const DirectX::XMFLOAT2& origin,
        float rotation,
        float scale,
        float depth) noexcept :
        mPaused(false),
        mFrame(0),
        mSideFrameCount(0),
        mWarpFrameCount(0),
        mTextureWidth(0),
        mTextureHeight(0),
        mTimePerFrame(0.f),
        mTotalElapsed(0.f),
        mDepth(depth),
        mRotation(rotation),
        mOrigin(origin),
        mScale(scale, scale)
    {
    }

    AnimatedTexture(AnimatedTexture&&) = default;
    AnimatedTexture& operator= (AnimatedTexture&&) = default;

    AnimatedTexture(AnimatedTexture const&) = default;
    AnimatedTexture& operator= (AnimatedTexture const&) = default;

    void Load(ID3D11ShaderResourceView* texture, int warpFrameCount, int sideFrameCount, int framesPerSecond)
    {
        if (sideFrameCount < 0 || framesPerSecond <= 0)
            throw std::invalid_argument("AnimatedTexture");

        mPaused = false;
        mFrame = 0;
        mSideFrameCount = sideFrameCount;
        mWarpFrameCount = warpFrameCount;
        mTimePerFrame = 1.f / float(framesPerSecond);
        mTotalElapsed = 0.f;
        mTexture = texture;

        if (texture)
        {
            Microsoft::WRL::ComPtr<ID3D11Resource> resource;
            texture->GetResource(resource.GetAddressOf());

            D3D11_RESOURCE_DIMENSION dim;
            resource->GetType(&dim);

            if (dim != D3D11_RESOURCE_DIMENSION_TEXTURE2D)
                throw std::runtime_error("AnimatedTexture expects a Texture2D");

            Microsoft::WRL::ComPtr<ID3D11Texture2D> tex2D;
            resource.As(&tex2D);

            D3D11_TEXTURE2D_DESC desc;
            tex2D->GetDesc(&desc);

            mTextureWidth = int(desc.Width);
            mTextureHeight = int(desc.Height);
        }
    }

    void Update(float elapsed)
    {
        if (mPaused)
            return;

        mTotalElapsed += elapsed;

        if (mTotalElapsed > mTimePerFrame)
        {
            ++mFrame;
            mFrame = mFrame % (mWarpFrameCount * mSideFrameCount);
            mTotalElapsed -= mTimePerFrame;
        }
    }

    void Draw(DirectX::SpriteBatch* batch, const DirectX::XMFLOAT2& screenPos) const
    {
        DrawSprite(batch, mFrame, screenPos);
    }

    void DrawSprite(DirectX::SpriteBatch* batch, int frame, const DirectX::XMFLOAT2& screenPos) const
    {
        int frameWidth = mTextureWidth / mSideFrameCount;
        int frameHeight = mTextureHeight / mWarpFrameCount;

        RECT sourceRect;
        sourceRect.left = frameWidth * (frame % mSideFrameCount);
        sourceRect.top = frameHeight * (frame % mWarpFrameCount);
        sourceRect.right = sourceRect.left + frameWidth;
        sourceRect.bottom = sourceRect.top + frameHeight;

        batch->Draw(mTexture.Get(), screenPos, &sourceRect, DirectX::Colors::White,
            mRotation, mOrigin, mScale, DirectX::SpriteEffects_None, mDepth);
    }

    void Draw(DirectX::PrimitiveBatch<VertexPositionTexture>* batch, const DirectX::XMFLOAT3& pos, float width)const
    {
        DrawPrimitive(batch, mFrame, pos, width);
    }

    void DrawPrimitive(DirectX::PrimitiveBatch<VertexPositionTexture>* batch, int frame, const DirectX::XMFLOAT3& pos, float width)const
    {
        int frameWidth = mTextureWidth / mSideFrameCount;
        int frameHeight = mTextureHeight / mWarpFrameCount;

        float left, top, right, bottom;
        left = frameWidth * (frame % mSideFrameCount);
        top = frameHeight * (frame % mWarpFrameCount);
        right = left + frameWidth;
        bottom = top + frameHeight;

        VertexPositionTexture v1(Vector3(pos.x - width, pos.y, pos.z + width), Vector2(left / mTextureWidth, top / mTextureHeight));
        VertexPositionTexture v2(Vector3(pos.x + width, pos.y, pos.z + width), Vector2(right / mTextureWidth, top / mTextureHeight));
        VertexPositionTexture v3(Vector3(pos.x + width, pos.y, pos.z - width), Vector2(right / mTextureWidth, bottom / mTextureHeight));
        VertexPositionTexture v4(Vector3(pos.x - width, pos.y, pos.z - width), Vector2(left / mTextureWidth, bottom / mTextureHeight));

        batch->Begin();
        batch->DrawQuad(v1, v2, v3, v4);
        batch->End();
    }

    void Reset()
    {
        mFrame = 0;
        mTotalElapsed = 0.f;
    }

    void Stop()
    {
        mPaused = true;
        mFrame = 0;
        mTotalElapsed = 0.f;
    }

    void Play() { mPaused = false; }
    void Paused() { mPaused = true; }

    bool IsPaused() const { return mPaused; }

private:
    bool                                                mPaused;
    int                                                 mFrame;
    int                                                 mSideFrameCount;
    int                                                 mWarpFrameCount;
    int                                                 mTextureWidth;
    int                                                 mTextureHeight;
    float                                               mTimePerFrame;
    float                                               mTotalElapsed;
    float                                               mDepth;
    float                                               mRotation;
    DirectX::XMFLOAT2                                   mOrigin;
    DirectX::XMFLOAT2                                   mScale;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>    mTexture;
};