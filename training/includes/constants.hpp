#pragma once

inline const int STATE_DIM = 6; // Number of inputs in my DQN
inline const int ACTION_DIM = 3; // Number of outputs in my DQN

inline const int REPLAY_CAPACITY = 20000;
inline const int BATCH_SIZE = 64;
inline const float GAMMA = 0.99f;
inline const float LR = 1e-3f;
inline const int TRAINING_EPISODES = 20000;
inline const int MAX_STEPS_PER_EPISODE = 1000;
inline const int TRAIN_AFTER = 1000;
inline const int TRAIN_EVERY = 4;
inline const float EPS_START = 1.0f;
inline const float EPS_END = 0.05f;
inline const float EPS_DECAY = 0.9995f;
