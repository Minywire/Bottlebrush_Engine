#include "KeyInput.h"

KeyInput::KeyInput(const std::vector<KeyType>& keys_to_monitor)
    : keys_to_monitor_(keys_to_monitor) {
  for (auto k : keys_to_monitor_) {
    keys_[k] = kNone;
  }
}

KeyInput::~KeyInput() { keys_.clear(); }

const std::vector<KeyInput::KeyType>& KeyInput::GetKeyTypes() const {
  return keys_to_monitor_;
}

KeyInput::KeyState KeyInput::GetKeyState(KeyType key) const {
  return keys_.at(key);
}

void KeyInput::SetKeyState(KeyType key, KeyState state) {
  auto it = keys_.find(key);

  if (it == keys_.end()) {
    throw std::out_of_range("Cannot not find key in key input map!");
  }

  keys_[key] = state;
}
