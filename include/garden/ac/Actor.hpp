#pragma once

#include "../bs/Base.hpp"

#include "common.hpp"

class Actor : public Base
{

public:

	using Angle16 = u16;
	using Angle3u16 = Vector<u16, 3>;

	Vector3& GetPosition() { return m_Position; }
	const Vector3& GetPosition() const { return m_Position; }
	Angle3u16& GetRotation() { return m_Rotation; }
	const Angle3u16& GetRotation() const { return m_Rotation; }
	float GetSpeed() const { return m_Speed; }
	void GetPositionTo(Vector3& out, Angle16 angle, float distance, bool withHeight = false) const;

private:

	Vector3 m_Position;
	Vector3 m_BackupPosition;
	Angle3u16 m_Rotation;
	Angle3u16 m_BackupRotation;
	Angle3u16 m_PrevRotation;
	float m_Speed;
	float m_Unk;
};
ASSERT_SIZE(Actor, 0x48);
