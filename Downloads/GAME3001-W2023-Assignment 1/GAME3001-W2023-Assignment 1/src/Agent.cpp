#include "Agent.h"

#include "Util.h"

Agent::Agent()
{
	// Initialize the whisker colour
	m_lineColour[0] = glm::vec4(0, 1, 0, 1); // green colour for left whisker
	m_lineColour[1] = glm::vec4(0, 1, 0, 1); // green colour for middle whisker
	m_lineColour[2] = glm::vec4(0, 1, 0, 1); // green colour for right whisker

	// Initialize the whisker Collision booleans
	m_collisionWhiskers[0] = false;
	m_collisionWhiskers[1] = false;
	m_collisionWhiskers[2] = false;

	m_whiskerAngle = 45;
}

Agent::~Agent()
= default;

glm::vec2 Agent::GetTargetPosition() const
{
	return m_targetPosition;
}

glm::vec2 Agent::GetCurrentDirection() const
{
	return m_currentDirection;
}

float Agent::GetLOSDistance() const
{
	return m_LOSDistance;
}

bool Agent::HasLOS() const
{
	return m_hasLOS;
}

float Agent::GetCurrentHeading() const
{
	return m_currentHeading;
}

glm::vec4 Agent::GetLOSColour() const
{
	return m_LOSColour;
}

glm::vec2 Agent::GetLeftLOSEndPoint() const
{
	return m_leftLOSEndPoint;
}

glm::vec2 Agent::GetMiddleLOSEndPoint() const
{
	return m_middleLOSEndPoint;
}

glm::vec2 Agent::GetRightLOSEndPoint() const
{
	return m_rightLOSEndPoint;
}

bool* Agent::GetCollisionWhiskers()
{
	return m_collisionWhiskers;
}

glm::vec4 Agent::GetLineColour(const int index) const
{
	return m_lineColour[index];
}

float Agent::GetWhiskerAngle() const
{
	return m_whiskerAngle;
}

void Agent::SetLeftLOSEndPoint(const glm::vec2 point)
{
	m_leftLOSEndPoint = point;
}

void Agent::SetMiddleLOSEndPoint(const glm::vec2 point)
{
	m_middleLOSEndPoint = point;
}

void Agent::SetRightLOSEndPoint(const glm::vec2 point)
{
	m_rightLOSEndPoint = point;
}

void Agent::SetLineColour(const int index, const glm::vec4 colour)
{
	m_lineColour[index] = colour;
}

void Agent::SetWhiskerAngle(float angle)
{
	m_whiskerAngle = angle;
}

void Agent::UpdateWhiskers(const float angle)
{
	m_whiskerAngle = angle;

	// center / middle whisker
	SetMiddleLOSEndPoint(GetTransform()->position + GetCurrentDirection() * GetLOSDistance());

	// left whisker
	float x = sin((GetCurrentHeading() - m_whiskerAngle + 90.0f) * Util::Deg2Rad);
	float y = cos((GetCurrentHeading() - m_whiskerAngle + 90.0f) * Util::Deg2Rad);
	SetLeftLOSEndPoint(GetTransform()->position + glm::vec2(x, -y) * GetLOSDistance() * 0.75f);

	// right whisker
	x = sin((GetCurrentHeading() + m_whiskerAngle + 90.0f) * Util::Deg2Rad);
	y = cos((GetCurrentHeading() + m_whiskerAngle + 90.0f) * Util::Deg2Rad);
	SetRightLOSEndPoint(GetTransform()->position + glm::vec2(x, -y) * GetLOSDistance() * 0.75f);
}

void Agent::SetTargetPosition(const glm::vec2 new_position)
{
	m_targetPosition = new_position;
}

void Agent::SetCurrentDirection(const glm::vec2 new_direction)
{
	m_currentDirection = new_direction;
}

void Agent::SetLOSDistance(const float distance)
{
	m_LOSDistance = distance;
}

void Agent::SetHasLOS(const bool state)
{
	m_hasLOS = state;
	m_LOSColour = (m_hasLOS) ? glm::vec4(0, 1, 0, 1) : glm::vec4(1, 0, 0, 1);
}

void Agent::SetCurrentHeading(const float heading)
{
	m_currentHeading = heading;
	ChangeDirection();
}

void Agent::SetLOSColour(const glm::vec4 colour)
{
	m_LOSColour = colour;
}

void Agent::ChangeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);
}
