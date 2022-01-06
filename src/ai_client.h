#pragma once

#include <HL/playable_client.h>
#include <HL/bspfile.h>

class AiClient : public HL::PlayableClient
{
private:
	const float PlayerHeightStand = 72.0f;
	const float PlayerHeightDuck = 36.0f;
	const float PlayerOriginZStand = 36.0f;
	const float PlayerOriginZDuck = 18.0f;
	const float PlayerWidth = 32.0f;
	const float StepHeight = 18.0f; // if delta Z is greater than this, we have to jump to get up
	const float JumpHeight = 41.8f; // if delta Z is less than this, we can jump up on it
	const float JumpCrouchHeight = 58.0f; // (48) if delta Z is less than or equal to this, we can jumpcrouch up on it
	const float MaxDistance = 8192.0f;

public:
	AiClient();

protected:
	void initializeGameEngine() override;
	void initializeGame() override;
	void think(HL::Protocol::UserCmd& cmd);
	void testMove(HL::Protocol::UserCmd& cmd);
	glm::vec3 getOrigin() const;
	glm::vec3 getFootOrigin() const;
	bool isVisible(const glm::vec3& target) const;
	bool isVisible(const HL::Protocol::Entity& entity) const;
	bool isOnGround() const;
	bool isOnLadder() const;
	float getDistance(const glm::vec3& target) const;
	float getDistance(const HL::Protocol::Entity& entity) const;
	void moveTo(HL::Protocol::UserCmd& cmd, const glm::vec3& target) const;
	void moveTo(HL::Protocol::UserCmd& cmd, const HL::Protocol::Entity& entity) const;
	void moveFrom(HL::Protocol::UserCmd& cmd, const glm::vec3& target) const;
	void moveFrom(HL::Protocol::UserCmd& cmd, const HL::Protocol::Entity& entity) const;
	void lookAt(HL::Protocol::UserCmd& cmd, const glm::vec3& target) const;
	void lookAt(HL::Protocol::UserCmd& cmd, const HL::Protocol::Entity& entity) const;
	void jump();
	void duck();

	void trivialMoveTo(HL::Protocol::UserCmd& cmd, const glm::vec3& target);

public:
	void setMoveTarget(std::optional<glm::vec3> value) { mMoveTarget = value; }
	const auto& getMoveTarget() const { return mMoveTarget; }

	const auto& getBsp() const { return mBspFile; }

private:
	Clock::TimePoint mThinkTime = Clock::Now();
	BSPFile mBspFile;
	glm::vec3 mPrevViewAngles = { 0.0f, 0.0f, 0.0f };
	std::optional<glm::vec3> mMoveTarget;
	bool mWantJump = false;
	bool mWantDuck = false;
};