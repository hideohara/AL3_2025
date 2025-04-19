#pragma once

#include "KamataEngine.h"

/// <summary>
/// アフィン変換
/// </summary>
KamataEngine::Matrix4x4 MakeAffine(KamataEngine::Vector3 &scale, KamataEngine::Vector3 &rotation, KamataEngine::Vector3 &translation);
