//Îêñèíåì ñûí øëþøêè
#pragma once
#include <intrin.h>
#define CALLED_BY(func,off) (reinterpret_cast<std::uint64_t>(_ReturnAddress()) > func && reinterpret_cast<std::uint64_t>(_ReturnAddress()) < func + off)
RaycastHit hitResult;
Vector3 _aimdirection;
PlayerProjectileUpdate* ppu;
bool ppu_getted;
float lastshottime;
float proj_skip = 0.f;
#define maxx( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#define minm( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
inline Vector3 PerfectPrediction(bool aiming,bool predicted) {
	bool hasHit = Physics::RaycastQTI(LocalPlayer::Entity()->eyes()->position(), LocalPlayer::Entity()->eyes()->BodyForward(), &hitResult, 400.f, 256 | 2048 | 65536 | 1073741824 | 8388608 | 2097152 | 4194304 | 67108864 | 134217728 | 33554432 | 32768 | 8192 | 512 | 1, QueryTriggerInteraction::Ignore);

	if ((target_ply != nullptr && aiming) ||
		(funcs::weapon::aimhelper && !aiming && hitResult.point != Vector3::Zero())) {
		Vector3 actualtargetposition;
		std::vector<Vector3> closestPoints;
		auto activeWeaponID = LocalPlayer::Entity()->GetActiveWeapon()->GetID();
		if (activeWeaponID != 795236088 && activeWeaponID != 200773292 && activeWeaponID != 1525520776)
		{
			BaseProjectile* item = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
			BaseProjectile* held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
			auto classname = held->class_name( );
			if (item && held)
			{
				BasePlayer* target = reinterpret_cast<BasePlayer*>(target_ply);
				if ( !math::m_strcmp(classname, "BaseMelee") || !math::m_strcmp(classname, "Planner") || !math::m_strcmp(classname, "Hammer") )
				{
					if ( math::m_strcmp(classname, "BaseProjectile")
						|| math::m_strcmp(classname, "BowWeapon")
						|| math::m_strcmp(classname, "CompoundBowWeapon")
						|| math::m_strcmp(classname, "BaseLauncher")
						|| math::m_strcmp(classname, "CrossbowWeapon")
						|| math::m_strcmp(classname, "FlintStrikeWeapon") )
					{
						auto primaryMagazine = item->primaryMagazine();
						auto ammoType = primaryMagazine->ammoType();
						if (ammoType != 0)
						{
							auto itemmodproj = ammoType->GetComponent(Type::ItemModProjectile());
							auto m_CachedPtr = *(UINT_PTR*)(ammoType + 0x10);
							auto gameobj = *(UINT_PTR*)(m_CachedPtr + 0x30);
							auto ItemModProjectile = itemmodproj;
							float SimulatedTargetTime = 0.f;
							if (ItemModProjectile)
							{
								auto projectileObject = *(UINT_PTR*)(ItemModProjectile + 0x20);
								auto projectileType = (UINT_PTR)Type::GetType("Projectile, Assembly-CSharp");
								auto projectileClass = GetClassObject(projectileObject);
								UINT_PTR projectile = GetGameObjectComponent(projectileType, projectileClass);
								if (projectile)
								{
									float& integrity = *(float*)(projectile + O::Projectile::integrity);
									float& initialDistance = *(float*)(projectile + O::Projectile::initialDistance);
									Vector3& previousVelocity = *(Vector3*)(projectile + O::Projectile::previousVelocity);
									auto projectileVelocitymenu = *(float*)(ItemModProjectile + 0x3C);
									auto projectileVelocityScale = (funcs::weapon::lowvelocity ? funcs::weapon::bulletspeed : 1.f) * item->projectileVelocityScale();

									float velrnd = ItemModProjectile->GetRandVel();
									float drag = *(float*)(projectile + O::Projectile::drag);
									float gravityModifier = *(float*)(projectile + O::Projectile::gravityModifier);
									auto gravity = Physics::get_gravity();
									auto get_fixedDeltaTime = Time::fixedDeltaTime();
									auto get_timeScale = Time::get_timeScale();
									float deltaTime = get_fixedDeltaTime * get_timeScale;
									if (funcs::weapon::aimhelper && !aiming)
									{
										actualtargetposition = hitResult.point;
									}
									if (aiming)
									{
										if (funcs::other::BulletPos != Vector3(0, 0, 0))
										{
											actualtargetposition = funcs::other::BulletPos;
										}
										else
										{
											actualtargetposition = target->GetTransform(head)->position();
										}
									}
									Vector3 localPosition = LocalPlayer::Entity()->eyes()->position();
									Vector3 playerVelocity = Vector3(target->GetWorldVelocity().x, 0, target->GetWorldVelocity().z)/* * 0.75f*/;

									Vector3 targetPosition = actualtargetposition;
									_aimdirection = AimConeUtil::GetModifiedAimConeDirection(0.f, targetPosition - localPosition, false);
									float bulletTime = std::sqrt((actualtargetposition.x) * (actualtargetposition.x) + (actualtargetposition.z) * (actualtargetposition.z));
									int sims = 1;
									bool hitPlayers = false;
									float initalDistance = *(float*)(projectile + O::Projectile::initialDistance);
									while (sims < 30)
									{
										sims++;

										_aimdirection = AimConeUtil::GetModifiedAimConeDirection(0.f, targetPosition - localPosition, false);
										Vector3 velocity = _aimdirection * projectileVelocitymenu * projectileVelocityScale;
										Vector3 velocity2 = _aimdirection * velrnd;

										auto currentPosition = localPosition;
										auto previousPosition = currentPosition;

										Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);
										Vector3 offset = Vector3().Zero();
										

										//if (funcs::weapon::vlonetpeleport)
										//{
										//	auto desyncTimeClamped = minm(Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime(), 1.f);
										//	auto desyncTimeClampedServer = maxx(desyncTimeClamped - 0.03125f * 5.f, 0.2f);
										//	float num11 = desyncTimeClampedServer;
										//	float distanceToTarget = localPosition.distance(targetPosition);
										//	float magnitude2 = velocity.Magnitude();
										//	initalDistance = *(float*)(projectile + O::Projectile::initialDistance) + num11 * magnitude2;
										//	proj_skip = initalDistance;
										//}


										//if (funcs::weapon::vlonetpeleport && target_ply)
										//{
										//	auto activeWeaponID = LocalPlayer::Entity()->GetActiveWeapon()->GetID();
										//	if (activeWeaponID != 1953903201 && activeWeaponID != 884424049 && activeWeaponID != 1965232394 && activeWeaponID != 1443579727)
										//	{
										//		float timeSinceLastTick = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime());
										//		float last_tick_time = Mathf::Max(0.f, Mathf::Min(timeSinceLastTick, 1.f));
										//		float num = 1.5f;
										//		float eye_clientframes = 2.0f;
										//		float eye_serverframes = 2.0f;
										//		float num2 = eye_clientframes / 60.f;
										//		float num3 = eye_serverframes * Mathx::Max(Time::deltaTime(), Time::smoothDeltaTime(), Time::fixedDeltaTime());
										//		float num11 = ((last_tick_time < 0.05 ? 0.05 : last_tick_time) + num2 + num3) * num;
										//		/*float initialDist = prdoj->initialDistance() - 1.f;*/
										//		float magnitude2 = velocity2.Magnitude();
										//		float num23 = *(float*)(projectile + O::Projectile::initialDistance) + num11 * magnitude2;
										//		proj_skip = num23 - 0.03125f - *(float*)(projectile + O::Projectile::initialDistance);
										//	}
										//}

										for (int i = -1; i < ((int)(8.f / deltaTime)); i++)
										{
											previousPosition = currentPosition;
											currentPosition += velocity * deltaTime;
											velocity += gravity * gravityModifier * deltaTime;
											velocity -= velocity * drag * deltaTime;

											auto line = (currentPosition - previousPosition);
											auto len = line.UnityMagnitude();
											line.UnityNormalize();
											auto v = actualtargetposition - previousPosition;
											auto d = Vector3().UnityDot(v, line);

											if (d < 0.f)
											{
												d = 0.f;
											}
											else if (d > len)
											{
												d = len;
											}

											Vector3 nearestPoint = previousPosition + line * d;

											if (nearestPoint.distance(actualtargetposition) < 0.01f)
											{
												if (funcs::weapon::vlonetpeleport) {
													bulletTime = (i * deltaTime) - (proj_skip / velrnd);
												}
												else
												{
													bulletTime = i * deltaTime;
												}

												hitPlayers = true;
											}
											else if (nearestPoint.distance(actualtargetposition) < closestPoint.distance(actualtargetposition))
											{
												closestPoint = nearestPoint;
												offset = actualtargetposition - nearestPoint;
											}
										}

										if (hitPlayers) break;
										targetPosition += offset;
									}

									if (!predicted)
									{
										if (funcs::weapon::showtrajectory)
										{
											if (hitPlayers)
											{
												_aimdirection = AimConeUtil::GetModifiedAimConeDirection(0.f, targetPosition - localPosition, false);
												Vector3 velocity = _aimdirection * projectileVelocitymenu * projectileVelocityScale;

												auto currentPosition = localPosition;
												auto previousPosition = currentPosition;

												Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);
												Vector3 offset = Vector3().Zero();

												for (int i = -1; i < ((int)(8.f / deltaTime)); i++)
												{
													previousPosition = currentPosition;
													currentPosition += velocity * deltaTime;
													velocity += gravity * gravityModifier * deltaTime;
													velocity -= velocity * drag * deltaTime;

													auto line = (currentPosition - previousPosition);
													auto len = line.UnityMagnitude();
													line.UnityNormalize();
													auto v = actualtargetposition - previousPosition;
													auto d = Vector3().UnityDot(v, line);

													if (d < 0.f)
													{
														d = 0.f;
													}
													else if (d > len)
													{
														d = len;
													}

													Vector3 nearestPoint = previousPosition + line * d;
													if (nearestPoint.distance(actualtargetposition) < 0.01f)
													{
														hitPlayers = false;
													}
													else if (nearestPoint.distance(actualtargetposition) < closestPoint.distance(actualtargetposition))
													{
														closestPoint = nearestPoint;
														closestPoints.push_back(nearestPoint);
													}
												}
											}
										}
									}
									if (predicted)
									{
										if (bulletTime != 1337.f)
										{
											Vector3 finalVelocity = playerVelocity * bulletTime;

											actualtargetposition += finalVelocity;


											Vector3 targetPosition = actualtargetposition;
											_aimdirection = AimConeUtil::GetModifiedAimConeDirection(0.f, targetPosition - localPosition, false);
											float bulletTime = 1337.f;
											int sims = 0;
											while (sims < 30)
											{

												sims++;
												bool hitPlayer = false;

												_aimdirection = AimConeUtil::GetModifiedAimConeDirection(0.f, targetPosition - localPosition, false);
												Vector3 velocity = _aimdirection * projectileVelocitymenu * projectileVelocityScale;

												auto currentPosition = localPosition;
												auto previousPosition = currentPosition;

												Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);
												Vector3 offset = Vector3().Zero();

												for (int i = -1; i < ((int)(8.f / deltaTime)); i++)
												{
													previousPosition = currentPosition;
													currentPosition += velocity * deltaTime;
													velocity += gravity * gravityModifier * deltaTime;
													velocity -= velocity * drag * deltaTime;

													auto line = (currentPosition - previousPosition);

													auto len = line.UnityMagnitude();
													line.UnityNormalize();
													auto v = actualtargetposition - previousPosition;
													auto d = Vector3().UnityDot(v, line);

													if (d < 0.f)
													{
														d = 0.f;
													}
													else if (d > len)
													{
														d = len;
													}



													Vector3 nearestPoint = previousPosition + line * d;

													if (nearestPoint.distance(actualtargetposition) < 0.1f)
													{
														if (funcs::weapon::vlonetpeleport) {
															bulletTime = (i * deltaTime) - (proj_skip / velrnd);
														}
														else
														{
															bulletTime = i * deltaTime;
														}
														hitPlayer = true;
													}
													else if (nearestPoint.distance(actualtargetposition) < closestPoint.distance(actualtargetposition))
													{
														closestPoint = nearestPoint;
														offset = actualtargetposition - nearestPoint;
													}
												}

												if (hitPlayer) break;
												targetPosition += offset;
											}
											return _aimdirection;
										}
									}
									if (!predicted)
									{
										if (funcs::weapon::showtrajectory)
										{
											for (int i = 0; i < closestPoints.size(); i++) {
												if (closestPoints[i] != Vector3::Zero() && closestPoints[i + 1] != Vector3::Zero() &&
													LineOfSight(closestPoints[i], closestPoints[i + 2]) && closestPoints[i + 1].distance(closestPoints[i]) < (LocalPlayer::Entity()->eyes()->position().distance(closestPoints[0]) + 0.5)) {
													DDraw::Line(closestPoints[i], closestPoints[i + 1], Color(1, 1, 1, 1), 0.01f, false, true);
												}
												else if (closestPoints[i] != Vector3::Zero() && actualtargetposition.distance(closestPoints[i]) < (LocalPlayer::Entity()->eyes()->position().distance(closestPoints[i]) + 0.5))
													DDraw::Line(closestPoints[i], actualtargetposition, Color(1, 1, 1, 1), 0.01f, false, true);
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

inline Vector3 GetModifiedAimConeDirection_hk(float aimCone, Vector3 inputVec, bool anywhereInside = true) {
	if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return AimConeUtil::GetModifiedAimConeDirection(aimCone, inputVec, anywhereInside);
	bool psalo = funcs::psilent::psilent && ((GetAsyncKeyState(funcs::psilent::key) && funcs::psilent::autoshottype == 1) ||
		funcs::psilent::autoshottype == 0 || funcs::psilent::autoshottype == 2 ||
		(funcs::psilent::autoshottype == 2 && GetAsyncKeyState(funcs::manipulator::manipulatorkey)));
	bool aiming = (target_ply != nullptr && psalo) ||
		(funcs::weapon::aimhelper && !psalo && hitResult.point != Vector3::Zero());
		did_reload = false;
		just_shot = true;
		fixed_time_last_shot = Time::fixedTime();
		if (funcs::weapon::recoilas) aimCone *= funcs::weapon::spread;
		else aimCone *= 1;
		PerfectPrediction(psalo, true);
	if (!aiming)
		return AimConeUtil::GetModifiedAimConeDirection(aimCone, inputVec, anywhereInside);
	else
		return _aimdirection;
}

int number = 0;
inline Attack* BuildAttackMessage_hk(HitTest* self, BaseEntity* a2) {
	__try
	{
		
		if (!self) return self->BuildAttackMessage(a2);
		auto ret = self->BuildAttackMessage(a2);
		auto entity = BaseNetworkable::clientEntities()->Find<BasePlayer*>(ret->hitID());


		if (funcs::weapon::patrolhelihitboxoverride)
		{
			unsigned int PrefabId = *reinterpret_cast< UINT64* >( entity + 0x28 ); if ( !PrefabId ) return self->BuildAttackMessage(a2);
			
			if ( !entity->IsPlayer( ) && PrefabId == 3029415845 )
			{
				if (entity->health() <= 5000.0f)
					ret->hitBone() = StringPool::Get(xorstr_("tail_rotor_col"));
				else
					ret->hitBone() = StringPool::Get(xorstr_("engine_col"));
			}
		}

		auto localPlayer = LocalPlayer::Entity();
		if (localPlayer) {

			if (reinterpret_cast<BasePlayer*>(self->ignoreEntity())->userID() == localPlayer->userID()) {
				if (entity) {
					if (entity->IsPlayer()) {
						if (funcs::other::acrestrict == 1) {
							if (number % 2 == 0) {
								ret->hitBone() = StringPool::Get(xorstr_("head"));
								number += 1;
							}
							else {
								ret->hitBone() = StringPool::Get(xorstr_("spine3"));
								number += 1;
							}

						}
						else
						{
							if (funcs::weapon::hitoverride) {
								if (funcs::weapon::hitboxoverride == 1)
									ret->hitBone() = StringPool::Get(xorstr_("head"));
								else if (funcs::weapon::hitboxoverride == 2)
									ret->hitBone() = StringPool::Get(xorstr_("spine4"));
								else if (funcs::weapon::hitboxoverride == 3) {
									// yandere dev in this bitch
									int num = rand() % 100;

									if (num > 90)
										ret->hitBone() = StringPool::Get(xorstr_("head"));
									else if (num < 90 && num > 80)
										ret->hitBone() = StringPool::Get(xorstr_("neck"));
									else if (num < 80 && num > 70)
										ret->hitBone() = StringPool::Get(xorstr_("l_clavicle"));
									else if (num < 70 && num > 60)
										ret->hitBone() = StringPool::Get(xorstr_("pelvis"));
									else if (num < 60 && num > 50)
										ret->hitBone() = StringPool::Get(xorstr_("r_hip"));
									else if (num < 50 && num > 40)
										ret->hitBone() = StringPool::Get(xorstr_("r_foot"));
									else if (num < 40 && num > 30)
										ret->hitBone() = StringPool::Get(xorstr_("spine1"));
									else if (num < 30 && num > 20)
										ret->hitBone() = StringPool::Get(xorstr_("l_hand"));
									else if (num < 20 && num > 10)
										ret->hitBone() = StringPool::Get(xorstr_("r_upperarm"));
									else if (num < 10)
										ret->hitBone() = StringPool::Get(xorstr_("l_knee"));
									else
										ret->hitBone() = StringPool::Get(xorstr_("spine4"));
								}
								else if (funcs::weapon::hitboxoverride == 4) {
									// yandere dev in this bitch
									int num = rand() % 100;

									if (num > 90)
										ret->hitBone() = StringPool::Get(xorstr_("pelvis"));
									else if (num < 90 && num > 80)
										ret->hitBone() = StringPool::Get(xorstr_("spine4"));
									else if (num < 80 && num > 70)
										ret->hitBone() = StringPool::Get(xorstr_("l_clavicle"));
									else if (num < 70 && num > 60)
										ret->hitBone() = StringPool::Get(xorstr_("pelvis"));
									else if (num < 60 && num > 50)
										ret->hitBone() = StringPool::Get(xorstr_("r_hip"));
									else if (num < 50 && num > 40)
										ret->hitBone() = StringPool::Get(xorstr_("r_foot"));
									else if (num < 40 && num > 30)
										ret->hitBone() = StringPool::Get(xorstr_("spine1"));
									else if (num < 30 && num > 20)
										ret->hitBone() = StringPool::Get(xorstr_("l_hand"));
									else if (num < 20 && num > 10)
										ret->hitBone() = StringPool::Get(xorstr_("r_upperarm"));
									else if (num < 10)
										ret->hitBone() = StringPool::Get(xorstr_("l_knee"));
									else
										ret->hitBone() = StringPool::Get(xorstr_("spine4"));
								}
								else if (funcs::weapon::hitboxoverride == 5) {
									int yeet = rand() % 100;
									if (yeet > 50)
										ret->hitBone() = StringPool::Get(xorstr_("head"));
									else
										ret->hitBone() = StringPool::Get(xorstr_("spine4"));
								}
							}
						}


					}
				}
			}
		}
		return ret;
	}
	__except (true)
	{
	}
}
void ProjectileUpdate_hk(Projectile* projectile) {
	__try
	{
		if (funcs::weapon::thickbullet)
			projectile->thickness() = 0.7f;
		else
			projectile->thickness() = 0.1f;
		float offset = 0.f;

		if (projectile->isAuthoritative() &&
			patrol_helicopter != nullptr &&
			funcs::weapon::helimagic)
		{

			Vector3 tar = reinterpret_cast<BaseEntity*>(patrol_helicopter)->transform()->position();
			if (LineOfSight(tar, projectile->currentPosition()) && math::_3distance(projectile->currentPosition(), tar) < 35.0f) {
				if (projectile->traveledDistance() > 35.0f) {
					Transform* transform = reinterpret_cast<BaseEntity*>(patrol_helicopter)->transform();

					HitTest* hitTest = projectile->hitTest();
					hitTest->DidHit() = true;
					hitTest->HitEntity() = (BaseEntity*)patrol_helicopter;
					hitTest->HitTransform() = transform;
					hitTest->HitPoint() = transform->InverseTransformPoint(projectile->currentPosition());
					hitTest->HitNormal() = transform->InverseTransformDirection(projectile->currentPosition());
					hitTest->AttackRay() = Ray(projectile->currentPosition(), tar - projectile->currentPosition());
					projectile->DoHit(hitTest, hitTest->HitPointWorld(), hitTest->HitNormalWorld());

				}
			}
		}
	}
	__except (true)
	{
	}
	return projectile->Update();
}

inline void DoAttack_hk(FlintStrikeWeapon* weapon) noexcept {
	__try
	{
		if (!weapon) return;
		if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return weapon->DoAttack();
		if (funcs::weapon::instaeoka)
			weapon->_didSparkThisFrame() = true;
	}
	__except (true)
	{
		if (funcs::weapon::instaeoka)
			weapon->_didSparkThisFrame() = false;
	}
	return weapon->DoAttack();
}


//inline void loadprank_hk(BasePlayer* self, BaseNetworkable::LoadInfo* info) {
//
//	return self->Load(0);
//}


inline Vector3 BodyLeanOffset_hk(PlayerEyes* a1) noexcept {
	__try
	{
		if (!a1) return Vector3::Zero();
		if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return a1->BodyLeanOffset();
		Vector3 targetheadpos = funcs::other::BulletPos != Vector3::Zero() ? funcs::other::BulletPos : target_ply->BonePosition(AimSpotInt);
		bool DesyncMode = funcs::manipulator::desyncmode == 1 ? funcs::manipulator::manipulator && GetAsyncKeyState(funcs::manipulator::manipulatorkey) : funcs::manipulator::manipulator;
		if (DesyncMode) {
			if (target_ply != nullptr) {


				if ( !funcs::manipulator::m_manipulate.empty( ) && LocalPlayer::Entity( )->GetHeldEntity( ) ) {

					return funcs::manipulator::m_manipulate;
				}
					
			}
		}
	}
	__except (true)
	{
	}
	return a1->BodyLeanOffset();
}
inline void DoFirstPersonCamera_hk(PlayerEyes* a1, Component* cam) noexcept {
	__try
	{
		if (!a1 || !cam) return;
		a1->DoFirstPersonCamera(cam);
		bool DesyncMode = funcs::manipulator::desyncmode == 1 ? funcs::manipulator::manipulator && GetAsyncKeyState(funcs::manipulator::manipulatorkey) : funcs::manipulator::manipulator;
		if (DesyncMode) {
			Vector3 re_p = LocalPlayer::Entity()->transform()->position() + LocalPlayer::Entity()->transform()->up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);
			cam->transform()->set_position(re_p);
		}
	}
	__except (true)
	{
	}
}
inline bool CanAttack_hk(BasePlayer* self) noexcept {
	__try
	{
		if (!self) return false;
		if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return self->CanAttack();
		if (funcs::localplayer::noattackrestriction)
			return true;
	}
	__except (true)
	{
	}
	return self->CanAttack();
}
bool canjump = false;
inline void UpdateVelocity_hk(PlayerWalkMovement* self) noexcept {
	__try
	{
		if (!self) return;
		if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return self->UpdateVelocity();
		if (funcs::localplayer::spiderman)
		{
			self->capsule()->set_radius(0.43);
		}

		if (!self->flying()) {
			Vector3 vel = self->TargetMovement();
			float max_speed = (self->swimming() || self->Ducking() > 0.5) ? 1.7f : 5.6f;
			if (funcs::localplayer::bhop && GetAsyncKeyState(funcs::localplayer::bhopkey) ||
				funcs::localplayer::bhop && funcs::localplayer::bhopkey == 0) max_speed += 0.75f;
			if (funcs::localplayer::nosprintrestriction) {
				if (vel.length() > 0.f) {
					if (GetAsyncKeyState(funcs::localplayer::speedhackkey) && funcs::localplayer::speedhack)
						max_speed += funcs::localplayer::speedhackfloat / 25;

					//max_speed += 0.5f;
					Vector3 target_vel = Vector3(vel.x / vel.length() * max_speed, vel.y, vel.z / vel.length() * max_speed);
					self->TargetMovement() = target_vel;
				}
			}

		}
		if (funcs::flyhack::flyhack)
		{
			self->flying() = true;
			Vector3 targetmovement{};

			Quaternion rotation = LocalPlayer::Entity()->eyes()->rotation();

			if (GetAsyncKeyState('W') & 1)
				targetmovement += Vector3(0, -rotation.y, rotation.z);
			if (GetAsyncKeyState('S') & 1)
				targetmovement -= Vector3(0, rotation.y, rotation.z);
			if (GetAsyncKeyState('A') & 1)
				targetmovement -= Vector3(rotation.x, 0, 0);
			if (GetAsyncKeyState('D') & 1)
				targetmovement += Vector3(rotation.x, 0, 0);

			if (GetAsyncKeyState(VK_SPACE))
				targetmovement.y += 1.f;

			float d = 5.f;
			if (GetAsyncKeyState(VK_CONTROL))
				d = 2.5f;
			if (GetAsyncKeyState(VK_SHIFT))
				d = 10.f;

			if (!(targetmovement == Vector3{ 0.f, 0.f, 0.f }))
				self->TargetMovement() = targetmovement * d;
		}
		bool DesyncMode = funcs::manipulator::desyncmode == 1 ? funcs::manipulator::manipulator && GetAsyncKeyState(funcs::manipulator::manipulatorkey) : funcs::manipulator::manipulator;
		Vector3 current1 = LocalPlayer::Entity()->transform()->position();
		if (funcs::localplayer::walkonwater)
		{
			if (WaterLevel::Test(current1, true, false, LocalPlayer::Entity()))
			{
				self->gravityMultiplier() = 0.0f;
				self->flying() = true;
				LocalPlayer::Entity()->movement()->TeleportTo(Vector3(current1.x, current1.y + 0.05, current1.z));
				canjump = true;
			}
			else if (WaterLevel::Test(current1 - Vector3(0, 0.2, 0), true, false, LocalPlayer::Entity()))
			{
				self->flying() = false;
			}
		}
		if ((!WaterLevel::Test(current1 - Vector3(0, 0.2, 0), true, false, LocalPlayer::Entity()) && funcs::localplayer::walkonwater) ||
			!funcs::localplayer::walkonwater)
		{
			canjump = false;
			if (DesyncMode && funcs::manipulator::desyncmode != 0)
			{
				self->TargetMovement() = Vector3::Zero();
				self->jumpTime() = 0.f;
				self->grounded() = true;
				self->gravityMultiplier() = 0.f;
				LocalPlayer::Entity()->movement()->TeleportTo(LocalPlayer::Entity()->lastSentTick()->position());
			}
			else
			{
				if (!funcs::localplayer::gravity)
					self->gravityMultiplier() = 2.5f;// = 2.f;
				else
					self->gravityMultiplier() = funcs::localplayer::gravityfloat;
			}
		}
		

		//if (overrided != current)
			//player->movement()->TeleportTo(overrided);

	}
	__except (true)
	{
	}
	return self->UpdateVelocity();
}
inline Vector3 EyePositionForPlayer_hk(BaseMountable* mount, BasePlayer* player, Quaternion lookRot) noexcept {
	__try
	{
		if (!mount || !player) return Vector3::Zero();
		if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return mount->EyePositionForPlayer(player, lookRot);
		if (player->userID() == LocalPlayer::Entity()->userID()) {
			bool DesyncMode = funcs::manipulator::desyncmode == 1 ? funcs::manipulator::manipulator && GetAsyncKeyState(funcs::manipulator::manipulatorkey) : funcs::manipulator::manipulator;
			if (DesyncMode) {
				return mount->EyePositionForPlayer(player, lookRot) + funcs::manipulator::m_manipulate;
			}
		}
	}
	__except (true)
	{
	}
	return mount->EyePositionForPlayer(player, lookRot);
}
inline void HandleJumping_hk(PlayerWalkMovement* a1, ModelState* state, bool wantsJump, bool jumpInDirection = false) noexcept {
	__try
	{
		if (!a1 || !state || !wantsJump) return;
		if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return a1->HandleJumping(state, wantsJump, jumpInDirection);
		if (funcs::localplayer::nojumprestriction || (canjump && funcs::localplayer::walkonwater)) {
			if (!wantsJump)
				return;

			a1->grounded() = (a1->climbing() = (a1->sliding() = false));
			state->set_ducked(false);
			a1->jumping() = true;
			state->set_jumped(true);
			a1->jumpTime() = Time::time();
			a1->ladder() = nullptr;

			Vector3 curVel = a1->body()->velocity();
			a1->body()->set_velocity({ curVel.x, 10, curVel.z });
			return;
		}
	}
	__except (true)
	{
	}
	return a1->HandleJumping(state, wantsJump, jumpInDirection);
}
inline void OnLand_hk(BasePlayer* ply, float vel) noexcept {
	__try
	{
		if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return ply->OnLand(vel);
		if (!funcs::localplayer::nofalldamage)
			ply->OnLand(vel);
	}
	__except (true)
	{
	}
}

void BurstShot(int shotsLeft, BaseProjectile* held, Vector3 target, BasePlayer* plly) {
	float m = held->repeatDelay( ) * 0.75f;
	float timeSinceLastTick = ( Time::realtimeSinceStartup( ) - LocalPlayer::Entity( )->lastSentTickTime( ) );
	int r = timeSinceLastTick / m;

	if ( funcs::manipulator::burstshot && r > 1 && shotsLeft > 0 ) {
		float NextShot = lastshottime + held->repeatDelay( ) + 0.2;
		if ( Time::fixedTime( ) > NextShot ) {
			if ( LineOfSight(target, plly->eyes( )->position( )) ) {
				held->SendSignalBroadcast(BaseEntity::Signal::Attack, xorstr_(""));
				held->DoAttack( );
				held->LaunchProjectile( );
				held->primaryMagazine( )->contents( )--;
				held->UpdateAmmoDisplay( );
				held->ShotFired( );
				held->DidAttackClientside( );
				held->BeginCycle( );
			}

			if ( shotsLeft > 1 ) {
				BurstShot(shotsLeft - 1, held, target, plly);
			}
			else {
				lastshottime = Time::fixedTime( );
			}
		}
	}
}


inline void OnAttacked_hk(BaseCombatEntity* self, HitInfo* info) noexcept {
	__try
	{
		self->OnAttacked(info);
	}
	__except (true)
	{
	}
}

float LastUpdate = 0.f;
bool fly_bypass;
void update_chams(BasePlayer* players) {
	if (Time::realtimeSinceStartup() > LastUpdate + 10) {
		players->playerModel()->RebuildAll();
		LastUpdate = Time::realtimeSinceStartup();
	}
}
Vector3 lastpos = Vector3::Zero();
float w_last_syringe = 0.f;


int iarr = 0;
int iarr2 = 0;
float lasthittime = 0;
inline void ClientInput_hk(BasePlayer* plly, uintptr_t state) {
	if (!plly) plly = LocalPlayer::Entity();
	if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return plly->ClientInput(state);
	if (!state) return plly->ClientInput(state);

	bool psalo = funcs::psilent::psilent && ((GetAsyncKeyState(funcs::psilent::key) && funcs::psilent::autoshottype == 1) ||
		funcs::psilent::autoshottype == 0 || funcs::psilent::autoshottype == 2 ||
		(funcs::psilent::autoshottype == 2 && GetAsyncKeyState(funcs::manipulator::manipulatorkey)));
	PerfectPrediction(psalo, false);

	auto entityList = BaseNetworkable::clientEntities()->entityList();
	static bool Update = true;
	if (entityList) {
		static auto Bundle = AssetBundle::LoadFromFile(xorstr_("world.assets"));
		static auto Bundle2 = AssetBundle::LoadFromFile(xorstr_("newbundle"));
		if ( !skybox )
			skybox = Bundle2->LoadAsset<Material>(xorstr_("assets/skybox_7.jpg"), Type::GetType(xorstr_("UnityEngine.Material, UnityEngine.CoreModule")));
		if (!WireFrmaeRainbow)
			WireFrmaeRainbow = Bundle->LoadAsset<Material>(xorstr_("assets/shaders/rainbow wireframe.mat"), Type::GetType(xorstr_("UnityEngine.Material, UnityEngine.CoreModule")));
		if (!GlowVisibleCheck)
			GlowVisibleCheck = Bundle->LoadAsset<Shader>(xorstr_("assets/shaders/glow.shader"), Type::GetType(xorstr_("UnityEngine.Shader, UnityEngine.CoreModule")));
		if (!VisibleCheck)
			VisibleCheck = Bundle->LoadAsset<Shader>(xorstr_("assets/shaders/vischeck.shader"), Type::GetType(xorstr_("UnityEngine.Shader, UnityEngine.CoreModule")));
		if (!matcapfx2)
			matcapfx2 = Bundle->LoadAsset<Material>(xorstr_("assets/shaders/matcapfx_diffuse.mat"), Type::GetType(xorstr_("UnityEngine.Material, UnityEngine.CoreModule")));
		if (!matcapfx)
			matcapfx = Bundle->LoadAsset<Material>(xorstr_("assets/shaders/matcapfx_transparent_mask.mat"), Type::GetType(xorstr_("UnityEngine.Material, UnityEngine.CoreModule")));
		for (int i = 0; i < entityList->vals->size; i++) {
			BaseEntity* entity = *reinterpret_cast<BaseEntity**>(std::uint64_t(entityList->vals->buffer) + (0x20 + (sizeof(void*) * i)));
			if (!entity) continue;
			uintptr_t Object = *reinterpret_cast< uintptr_t* >( entity + 0x10 );
			if ( !Object ) continue;
			uintptr_t ObjectClass = *reinterpret_cast< uintptr_t* >( Object + 0x30 );
			if ( !ObjectClass ) continue;
			WORD tag = *reinterpret_cast< WORD* >( ObjectClass + 0x54 );
			unsigned int PrefabId = *reinterpret_cast< UINT64* >( entity + 0x28 );
			if ( funcs::localplayer::droptedchams)
			{
				if ( PrefabId == 3255145925 ) {
					entity->ChamsItems(entity);
				}
			}
			if ( tag == 6 )
			{
				BasePlayer* player = reinterpret_cast<BasePlayer*>(entity);
				if (funcs::localplayer::weaponchams || funcs::localplayer::heandchams)
					if (player && player->IsValid() && player->health() > 0.0f && player->lifestate() != BaseCombatEntity::LifeState::Dead && player == LocalPlayer::Entity())
					{
						static int count = 0;
						if (count < 60) {
							count++;
						}
						else {
							player->HandChams();
							count = 0;
						}
					}
				if (funcs::visuals::chamstype != 0) {
					if (player->lifestate() == BaseCombatEntity::LifeState::Dead) continue;
					if (player->HasPlayerFlag(PlayerFlags::Sleeping) && !funcs::visuals::sleepers) continue;
					if (player->playerModel()->isNpc() && !funcs::visuals::npc) continue;
					if (player->userID() == LocalPlayer::Entity()->userID()) continue;

					if (!player->HasPlayerFlag(PlayerFlags::Sleeping) && player && player->IsValid() && player->health() > 0.0f && player->lifestate() != BaseCombatEntity::LifeState::Dead)
					{
						update_chams(player);
						if (!player->playerModel()->isNpc() && !player->HasPlayerFlag(PlayerFlags::Sleeping))
							player->Chams(Color(0, 1, 1, 1), Color(1, 0, 1, 1));
						if (player->playerModel()->isNpc() && funcs::visuals::npc)
							player->Chams(Color(0, 1, 0, 1), Color(1, 0, 0, 1));
						Update = false;
					}
				}
				else
				{
					Update = true;
					if (Update)
						update_chams(player);
					Update = false;
				}
			}
		}
	}
	if (funcs::localplayer::removebob || funcs::localplayer::removelower) {
		if (auto model = BaseViewModel::ActiveModel()) {
			if (funcs::localplayer::removebob) {
				auto bob = model->bob();
				bob->bobAmountRun() = 0.f;
				bob->bobAmountWalk() = 0.f;
				bob->bobSpeedRun() = 0.f;
				bob->bobSpeedWalk() = 0.f;
				bob->leftOffsetRun() = 0.f;
			}

			if (funcs::localplayer::removelower) {
				auto lower = model->lower();
				lower->lowerOnSprint() = false;
				lower->lowerWhenCantAttack() = false;
				lower->lowerScale() = 0.f;
				lower->shouldLower() = false;
			}
		}
	}
	if (plly->userID() == LocalPlayer::Entity()->userID()) {
		auto transform = target_ply->GetTransform(head)->position();
		if (funcs::psilent::a_spot == 0) {
			AimSpotInt = head;
		}
		if (funcs::psilent::a_spot == 1) {
			AimSpotInt = spine4;
		}
		if (funcs::psilent::a_spot == 2) {
			int num = rand() % 100;
			if (num > 90)
			{
				AimSpotInt = head;
			}
			else if (num < 90 && num > 80)
			{
				AimSpotInt = neck;
			}
			else if (num < 80 && num > 70)
			{
				AimSpotInt = r_hip;
			}
			else if (num < 70 && num > 60)
			{
				AimSpotInt = pelvis;
			}
			else if (num < 60 && num > 50)
			{
				AimSpotInt = l_clavicle;
			}
			else if (num < 50 && num > 40)
			{
				AimSpotInt = l_upperarm;
			}
			else if (num < 40 && num > 30)
			{
				AimSpotInt = l_foot;
			}
			else if (num < 30 && num > 20)
			{
				AimSpotInt = r_foot;
			}
			else if (num < 20 && num > 10)
			{
				AimSpotInt = l_hand;
			}
			else if (num < 10)
			{
				AimSpotInt = r_hand;
			}
			else
			{
				AimSpotInt = spine1;
			}
		}
		if (funcs::psilent::a_spot == 3) {
			int num = rand() % 100;
			if (num > 90)
			{
				AimSpotInt = pelvis;
			}
			else if (num < 90 && num > 80)
			{
				AimSpotInt = spine4;
			}
			else if (num < 80 && num > 70)
			{
				AimSpotInt = r_hip;
			}
			else if (num < 70 && num > 60)
			{
				AimSpotInt = pelvis;
			}
			else if (num < 60 && num > 50)
			{
				AimSpotInt = l_clavicle;
			}
			else if (num < 50 && num > 40)
			{
				AimSpotInt = l_upperarm;
			}
			else if (num < 40 && num > 30)
			{
				AimSpotInt = l_foot;
			}
			else if (num < 30 && num > 20)
			{
				AimSpotInt = r_foot;
			}
			else if (num < 20 && num > 10)
			{
				AimSpotInt = l_hand;
			}
			else if (num < 10)
			{
				AimSpotInt = r_hand;
			}
			else
			{
				AimSpotInt = spine4;
			}
		}
		if (funcs::psilent::a_spot == 4) {
			int yeet1 = rand() % 100;
			if (yeet1 > 50) {
				AimSpotInt = head;
			}
			else {
				AimSpotInt = spine4;
			}
		}

		if (funcs::localplayer::weaponchams || funcs::localplayer::heandchams)
			ConVar::Graphics::chamsfix() = false;
		Vector3 vector1 = (plly->lastSentTick()->position() + plly->transform()->position()) * 0.5f;
		float radius2 = plly->GetRadius();
		float height2 = plly->GetHeight(false);


		bool DesyncMode = funcs::manipulator::desyncmode == 1 ? funcs::manipulator::manipulator && GetAsyncKeyState(funcs::manipulator::manipulatorkey) : funcs::manipulator::manipulator;
		if (DesyncMode)
			plly->clientTickInterval() = funcs::manipulator::maxdesyncfloat;
		else if (!funcs::weapon::fakelags1)
			plly->clientTickInterval() = 0.05f;

		if (!DesyncMode && funcs::weapon::fakelags1)
			plly->clientTickInterval() = funcs::localplayer::lagsam;


		if (funcs::localplayer::teleporttohead && GetAsyncKeyState(funcs::localplayer::teleporttoheadkey) && cheater_train_target != nullptr && LocalPlayer::Entity()->BonePosition(head).distance(cheater_train_target->BonePosition(head)) < 3.f)
		{
			Vector3 target = cheater_train_target->BonePosition(head);

			ImVec2 center(target.x, target.z);
			float radius = 0.5f;
			int numLines = 1;
			float angleStep = 2 * IM_PI / numLines;
			static float rotation = 0.0f;
			rotation += 0.08f;

			for (int i = 0; i < numLines; ++i) {
				float angle = i * angleStep + rotation;

				ImVec2 startPoint = rotatePoint1(ImVec2(center.x + radius, center.y), center, angle);
				Vector3 teleportPos(startPoint.x, target.y + 0.04f, startPoint.y);
				LocalPlayer::Entity()->movement()->TeleportTo(teleportPos);
			}

		}
		if (funcs::localplayer::teleportsphere)
		{
			RaycastHit tpsphereray;
			bool validCol = Physics::RaycastQTI(MainCamera::Camera()->Get_Position(), MainCamera::Camera()->Get_Forward(), &tpsphereray, 400.f, 256 | 2048 | 65536 | 1073741824 | 8388608 | 2097152 | 4194304 | 67108864 | 134217728 | 33554432 | 32768 | 8192 | 512 | 1, QueryTriggerInteraction::Ignore);
			if (validCol) {
				DDraw::Capsule(tpsphereray.point, Quaternion(), pulsation(0.1, 0.5, 0.5), 2 * pulsation(0.1, 0.5, 0.5), Color(funcs::localplayer::teleportspherecol[0], funcs::localplayer::teleportspherecol[1], funcs::localplayer::teleportspherecol[2], 1.f), 0.0001f, false, true);
			}
			if (GetAsyncKeyState(funcs::localplayer::teleportspherekey))
			{
				LocalPlayer::Entity()->movement()->TeleportTo(tpsphereray.point);
			}
		}

		float desyncTime = (Time::realtimeSinceStartup() - plly->lastSentTickTime()) - 0.03125 * 3;
		funcs::manipulator::desync = (0.1f + (((desyncTime)+2.f / 60.f + 0.125f) * 1.5f) * plly->GetMaxSpeed()) - 0.05f;

		BaseProjectile* held = held = plly->GetHeldEntity<BaseProjectile>();
		auto classnameheld = held->class_name( );
		BaseMelee* melee = LocalPlayer::Entity()->GetHeldEntity<BaseMelee>();
		auto classnamemelee = held->class_name( );

		if (held) {
			auto activeWeaponID = LocalPlayer::Entity()->GetActiveWeapon()->GetID();
			if (activeWeaponID != 795236088 && activeWeaponID != 200773292 && activeWeaponID != 1525520776)
			{
				Item* weapon = LocalPlayer::Entity()->GetHeldItem();
				if (w_last_syringe == 0.f) {
					w_last_syringe = LocalPlayer::Entity()->lastSentTickTime();
				}
				if (funcs::localplayer::instaheal && (weapon->info()->itemid() == 1079279582 || weapon->info()->itemid() == -2072273936) && LocalPlayer::Entity()->health() < 99) {
					if (LocalPlayer::Entity()->lastSentTickTime() > w_last_syringe + 0.7f) {
						held->ServerRPC(xorstr_("UseSelf"));
						w_last_syringe = LocalPlayer::Entity()->lastSentTickTime();
					}
				}
				if (funcs::weapon::fastbow && math::m_strcmp(classnameheld, "BowWeapon") ) {
					held->arrowBack() = 1.f;
					held->attackReady() = true;
				}
				if (funcs::weapon::automatic)
				{
					held->automatic() = true;
				}

				if (funcs::weapon::rapidfire && math::m_strcmp(classnameheld, "BaseProjectile") ) {
					held->repeatDelay() = 0.07f;
				}

				if (funcs::weapon::instchargecompound && math::m_strcmp(classnameheld, "CompoundBowWeapon"))
					reinterpret_cast<CompoundBowWeapon*>(held)->currentHoldProgress() = 1.5f;
				if (funcs::weapon::fakeshots && GetAsyncKeyState(funcs::weapon::fakeshotskey))
					held->SendSignalBroadcast(BaseEntity::Signal::Attack, xorstr_(""));
				float lastShotTime = held->lastShotTime() - GLOBAL_TIME;
				float reloadTime = held->nextReloadTime() - GLOBAL_TIME;
				Vector3 target = target_ply->BonePosition(AimSpotInt);

				if (target_ply == nullptr || !funcs::weapon::bulletteleport || !funcs::weapon::hitscan || LineOfSight(target_ply->BonePosition(head), LocalPlayer::Entity()->eyes()->position())) {
					funcs::other::BulletPos = Vector3::Zero();
				}

				if (!DesyncMode && !LineOfSight(target_ply->BonePosition(head), LocalPlayer::Entity()->eyes()->position()))
				{
					CalculateValidHitS_pos(LocalPlayer::Entity()->eyes()->position());
				}
				
				if (funcs::other::BulletPos != Vector3::Zero())
				{
					target = funcs::other::BulletPos;
				}
				else
				{
					target = target_ply->BonePosition(AimSpotInt);
				}
				if ( target_ply != nullptr && ( GetAsyncKeyState(funcs::psilent::key) && funcs::psilent::autoshottype == 1 ) ||
					funcs::psilent::autoshottype == 2 && GetAsyncKeyState(funcs::manipulator::manipulatorkey) ) {
					if ( LineOfSight(target, LocalPlayer::Entity( )->eyes( )->position( )) ) {
						if ( !math::m_strcmp(classnameheld, "BaseMelee") || !math::m_strcmp(classnameheld, "Planner") || !math::m_strcmp(classnameheld, "Hammer") ) {
							if ( held && ( math::m_strcmp(classnameheld, "BaseProjectile") )
								|| math::m_strcmp(classnameheld, "BowWeapon")
								|| math::m_strcmp(classnameheld, "CompoundBowWeapon")
								|| math::m_strcmp(classnameheld, "BaseLauncher")
								|| math::m_strcmp(classnameheld, "CrossbowWeapon")
								|| math::m_strcmp(classnameheld, "FlintStrikeWeapon") )
							{
								auto m = held->repeatDelay( ) * 0.75f;
								float timeSinceLastTick = ( Time::realtimeSinceStartup( ) - LocalPlayer::Entity( )->lastSentTickTime( ) );
								int r = timeSinceLastTick / m;
								if ( funcs::manipulator::burstshot && r > 1 ) {
									BurstShot(r, held, target, plly);
								}
								else {
									if ( !held->HasReloadCooldown( ) && !held->HasAttackCooldown( ) && reloadTime < 1.0f &&
										!held->Empty( ) && target_ply != nullptr && target_ply->IsValid( ) && LocalPlayer::Entity( )->HasPlayerFlag(PlayerFlags::Connected) && held->nextAttackTime( ) < Time::time( ) )
									{
										if ( LineOfSight(target, plly->eyes( )->position( )) ) {
											lastshottime = Time::fixedTime( );
											held->SendSignalBroadcast(BaseEntity::Signal::Attack, xorstr_(""));
											held->DoAttack( );
											held->LaunchProjectile( );
											held->primaryMagazine( )->contents( )--;
											held->UpdateAmmoDisplay( );
											held->ShotFired( );
											held->DidAttackClientside( );
											held->BeginCycle( );
											held->StartAttackCooldown(held->repeatDelay( ));
										}
									}
								}

								
								
								
							}
						}
						if ( math::m_strcmp(classnameheld, "BaseMelee") && !math::m_strcmp(classnameheld, "Planner") || !math::m_strcmp(classnameheld, "Hammer") ) {
							if ( melee && melee != nullptr ) {
								if ( target_ply != nullptr && target_ply->IsValid( ) && LocalPlayer::Entity( )->HasPlayerFlag(PlayerFlags::Connected) ) {
									if ( melee->HasAttackCooldown( ) || melee->nextAttackTime( ) >= Time::time( ) || melee->timeSinceDeploy( ) < melee->deployDelay( ) ) {}
									else {
										melee->SendSignalBroadcast(BaseEntity::Signal::Throw, xorstr_(""));
										melee->DoThrow( );
									}
								}
							}
						}
					}
				}
				if (funcs::weapon::silentreload)
				{
					auto activeWeaponID = LocalPlayer::Entity()->GetActiveWeapon()->GetID();
					if (activeWeaponID != 795236088 && activeWeaponID != 200773292 && activeWeaponID != 1525520776)
					{
						if ( !math::m_strcmp(classnameheld, "BaseMelee") || !math::m_strcmp(classnameheld, "Planner") || !math::m_strcmp(classnameheld, "Hammer") ) {

							BaseProjectile* ent = plly->GetHeldEntity<BaseProjectile>();
							if (ent) {
								BaseProjectile* held = held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
								if ( !math::m_strcmp(classnameheld, "BaseMelee") )
								{
									if (!did_reload)
										time_since_last_shot = (Time::fixedTime() - fixed_time_last_shot);

									if (just_shot && (time_since_last_shot > 0.2f))
									{
										ent->ServerRPC(xorstr_("StartReload"));
										ent->SendSignalBroadcast(BaseEntity::Signal::Reload);
										just_shot = false;
									}
									if (time_since_last_shot > (held->reloadTime() - (held->reloadTime() / 10))
										&& !did_reload)
									{
										ent->ServerRPC(xorstr_("Reload"));
										did_reload = true;
										time_since_last_shot = 0;
									}

								}
							}
						}
					}
				}
			}
		}
		else {
			funcs::other::BulletPos = Vector3(0, 0, 0);
			fixed_time_last_shot = Time::fixedTime();
		}
		if (DesyncMode && target_ply != nullptr)
			other::find_manipulate_angle();
		else
			if (!funcs::manipulator::m_manipulate.empty()) {
				funcs::manipulator::m_manipulate = Vector3::Zero();
			}
		funcs::manipulator::manipulated = DesyncMode;

		auto list = TOD_Sky::instances();
		if (list) {
			for (int j = 0; j < list->size; j++) {
				auto sky = (TOD_Sky*)list->get(j);
				if (!sky)
					continue;
				if (funcs::visuals::nightambientmultiplier)
					sky->Night()->AmbientMultiplier() = funcs::visuals::nightambient;
			}
		}

		GLOBAL_TIME = Time::time();
		Physics::IgnoreLayerCollision(30, 12, funcs::localplayer::noplayercollision);
		Physics::IgnoreLayerCollision(11, 12, funcs::localplayer::noplayercollision);
		if (funcs::localplayer::customerfov)
		{
			if (GetAsyncKeyState(funcs::localplayer::zoom) && funcs::localplayer::zoomhack)
				ConVar::Graphics::_fov() = funcs::localplayer::zoomamount;
			else
				ConVar::Graphics::_fov() = funcs::localplayer::fov;
		}
		else
			ConVar::Graphics::_fov() = 90.f;

		if (funcs::localplayer::customtime)
			BasePlayer::Admintime() = funcs::localplayer::timechander;
		else
			BasePlayer::Admintime() = -1;

		UINT64 klass = read(game_assembly + CO::TodSky, UINT64);
		UINT64 static_fields = read(klass + 0xB8, UINT64);
		UINT64 instances = read(static_fields, UINT64);
		UINT64 List1 = read(instances + 0x10, UINT64);
		UINT64 TOD_Sky = read(List1 + 0x20, UINT64);

		bool megacoder = false;
		if (funcs::visuals::SkyChanger)
		{
			auto days = *reinterpret_cast<DWORD64*>(TOD_Sky + 0x58);
			auto dsky_color = *reinterpret_cast<DWORD64*>(days + 0x28);
			auto dsky_gradient = *reinterpret_cast<DWORD64*>(dsky_color + 0x10);
			*reinterpret_cast<Color*>(dsky_gradient) = Color(funcs::visuals::SkyCol[0], funcs::visuals::SkyCol[1], funcs::visuals::SkyCol[2], 1);

			auto nights = *reinterpret_cast<DWORD64*>(TOD_Sky + 0x60);
			auto nsky_color = *reinterpret_cast<DWORD64*>(nights + 0x28);
			auto nsky_gradient = *reinterpret_cast<DWORD64*>(nsky_color + 0x10);
			*reinterpret_cast<Color*>(nsky_gradient) = Color(funcs::visuals::SkyCol[0], funcs::visuals::SkyCol[1], funcs::visuals::SkyCol[2], 1);
			megacoder = true;
		}
		if (!funcs::visuals::SkyChanger && megacoder) {
			auto days = *reinterpret_cast<DWORD64*>(TOD_Sky + 0x58);
			auto dsky_color = *reinterpret_cast<DWORD64*>(days + 0x28);
			auto dsky_gradient = *reinterpret_cast<DWORD64*>(dsky_color + 0x10);
			*reinterpret_cast<Color*>(dsky_gradient) = Color(255, 255, 255, 0.001);

			auto nights = *reinterpret_cast<DWORD64*>(TOD_Sky + 0x60);
			auto nsky_color = *reinterpret_cast<DWORD64*>(nights + 0x28);
			auto nsky_gradient = *reinterpret_cast<DWORD64*>(nsky_color + 0x10);
			*reinterpret_cast<Color*>(nsky_gradient) = Color(0, 0, 0, 0.001);
		}

		if (funcs::localplayer::spiderman)
		{
			LocalPlayer::Entity()->movement()->groundAngle() = 0.f;
			LocalPlayer::Entity()->movement()->groundAngleNew() = 0.f;
		}
		if (funcs::localplayer::fakeadmin && !funcs::localplayer::istrueadmin)
			plly->playerFlags() |= PlayerFlags::IsAdmin;

		if (funcs::localplayer::noattackrestriction)
			if (plly->mounted())
				plly->mounted()->canWieldItems() = true;

		if (funcs::weapon::hamerdrawing)
		{
			auto activeWeaponID = LocalPlayer::Entity()->GetActiveWeapon()->GetID();
			BaseProjectile* held = LocalPlayer::Entity( )->GetHeldEntity<BaseProjectile>( );
			auto classname = held->class_name( );
			if ( math::m_strcmp(classname, "Hammer") )
			{
				std::array<Vector3, 81> arr = {
					LocalPlayer::Entity()->transform()->position() + Vector3(1.0, 3.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.9, 3.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.8, 3.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.7, 3.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.6, 3.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.5, 3.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.4, 3.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.3, 3.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.2, 3.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.1, 3.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 3.0, 0.0),

					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 2.9, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 2.8, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 2.7, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 2.6, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 2.5, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 2.4, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 2.3, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 2.2, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 2.1, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 2.0, 0.0),


					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 1.9, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 1.8, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 1.7, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 1.6, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 1.5, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 1.4, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 1.3, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 1.2, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 1.1, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.0, 1.0, 0.0),

					LocalPlayer::Entity()->transform()->position() + Vector3(-0.1, 1.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.2, 1.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.3, 1.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.4, 1.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.5, 1.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.6, 1.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.7, 1.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.8, 1.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.9, 1.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-1.0, 1.0, 0.0),


					LocalPlayer::Entity()->transform()->position() + Vector3(-0.1, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.2, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.3, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.4, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.5, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.6, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.7, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.8, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-0.9, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-1.0, 2.0, 0.0),

					LocalPlayer::Entity()->transform()->position() + Vector3(-1.0, 2.1, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-1.0, 2.2, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-1.0, 2.3, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-1.0, 2.4, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-1.0, 2.5, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-1.0, 2.6, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-1.0, 2.7, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-1.0, 2.8, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-1.0, 2.9, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(-1.0, 3.0, 0.0),


					LocalPlayer::Entity()->transform()->position() + Vector3(0.1, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.2, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.3, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.4, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.5, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.6, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.7, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.8, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(0.9, 2.0, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(1.0, 2.0, 0.0),

					LocalPlayer::Entity()->transform()->position() + Vector3(1.0, 1.9, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(1.0, 1.8, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(1.0, 1.7, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(1.0, 1.6, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(1.0, 1.5, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(1.0, 1.4, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(1.0, 1.3, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(1.0, 1.2, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(1.0, 1.1, 0.0),
					LocalPlayer::Entity()->transform()->position() + Vector3(1.0, 1.0, 0.0)
				};

				if (iarr > 81) iarr = 0;
				if (Time::time() - lasthittime > 0.05f)
				{
					Vector3 hitpoint = arr[iarr];
					Vector3 origin = LocalPlayer::Entity()->eyes()->position();
					Vector3 localDir = LocalPlayer::Entity( )->eyes( )->BodyForward( );
					localDir.y = 0.00f;


					HitTest* hit = HitTest::New();
					hit->HitEntity() = NULL;
					hit->DidHit() = true;
					hit->MaxDistance() = melee->maxDistance();
					hit->HitTransform() = nullptr;
					/*hit->AttackRay() = Ray(origin, origin + (hitpoint - origin));*/
					hit->AttackRay( ) = Ray(hitpoint, Vector3(0.f, 0.f, 0.f));
					hit->HitNormal() = localDir;
					hit->HitPoint() = hitpoint;
					hit->HitMaterial() = System::String::New(xorstr_("glass"));
					melee->DoAttack(hit);
					lasthittime = Time::time();
					iarr += 1;
				}
			}
		}

		if (funcs::weapon::silentmelee) {
			BaseMelee* melee = LocalPlayer::Entity()->GetHeldEntity<BaseMelee>();
			auto classname = melee->class_name( );
			if (melee && melee != nullptr)
			{
				auto activeWeaponID = LocalPlayer::Entity()->GetActiveWeapon()->GetID();
				auto jackhammerorchainsaw = LocalPlayer::Entity()->GetHeldEntity();
				auto classnamej = jackhammerorchainsaw->class_name( );
				if (melee && melee != nullptr && math::m_strcmp(classname, "BaseMelee") ||
					jackhammerorchainsaw && jackhammerorchainsaw != nullptr && math::m_strcmp(classnamej, "Jackhammer") ||
					jackhammerorchainsaw && jackhammerorchainsaw != nullptr && math::m_strcmp(classnamej, "Chainsaw") )
					if (!math::m_strcmp(classnameheld, "Planner") && !math::m_strcmp(classnameheld, "Hammer"))
					{
						if (closest_ply != nullptr && target_ply != nullptr && closest_ply->health() > 0.0f && closest_ply->GetTransform(AimSpotInt)->position().distance(LocalPlayer::Entity()->eyes()->position()) <= melee->maxDistance() + 1.8f)
						{
							if (LineOfSight(closest_ply->GetTransform(AimSpotInt)->position(), LocalPlayer::Entity()->eyes()->position())) {
								if (closest_ply->IsValid() && melee && melee->nextAttackTime() < Time::fixedTime() &&
									melee->deployDelay() < melee->timeSinceDeploy())
								{
									auto trans = reinterpret_cast<BasePlayer*>(closest_ply)->GetTransform(head);
									if (trans)
									{
										Ray r = Ray(LocalPlayer::Entity()->eyes()->position(), ((closest_ply)->BonePosition(AimSpotInt) - LocalPlayer::Entity()->eyes()->position()).normalized());

										Vector3 origin = LocalPlayer::Entity()->eyes()->position();
										HitTest* hit = HitTest::New();
										hit->HitEntity() = closest_ply;
										hit->DidHit() = true;
										hit->MaxDistance() = melee->maxDistance();
										hit->HitTransform() = trans;
										hit->AttackRay() = r;
										hit->HitNormal() = trans->InverseTransformPoint((closest_ply)->BonePosition(AimSpotInt));
										hit->HitPoint() = trans->InverseTransformPoint((closest_ply)->BonePosition(AimSpotInt));
										melee->DoAttack(hit);
										melee->StartAttackCooldown(melee->repeatDelay());
									}
								}
							}
						}
					}
			}
		}
		if (funcs::localplayer::autocollect)
		{
			BaseEntity* collectibleEntity = BaseNetworkable::clientEntities()->FindClosest<BaseEntity*>("CollectibleEntity", LocalPlayer::Entity(), 3.0f);
			if (collectibleEntity && collectibleEntity != nullptr && collectibleEntity != 0x0)
				collectibleEntity->ServerRPC("Pickup");
		}

		if (funcs::weapon::silestlootstash)
		{
			BaseEntity* stash_object = BaseNetworkable::clientEntities()->FindClosest<BaseEntity*>("StashContainer", LocalPlayer::Entity(), 3.0f);
			if (stash_object && stash_object != nullptr)
				stash_object->ServerRPC("RPC_OpenLoot");

		}
		if (funcs::weapon::silestlootcorpes)
		{
			BaseEntity* player_object = BaseNetworkable::clientEntities()->FindClosest<BaseEntity*>("PlayerCorpse", LocalPlayer::Entity(), 5.f);
			if (player_object && player_object != nullptr)
				player_object->ServerRPC("RPC_LootCorpse");

			BaseEntity* board_object = BaseNetworkable::clientEntities()->FindClosest<BaseEntity*>("DroppedItemContainer", LocalPlayer::Entity(), 5.f);
			if (board_object && board_object != nullptr)
				board_object->ServerRPC("RPC_OpenLoot");


		}
		if (funcs::weapon::modelfck) {
			LocalPlayer::Entity()->playerModel()->PlayCinematic(System::String::New(xorstr_("Debug_TPose")));

		}
		if (funcs::weapon::silestlootmine)
		{
			BaseEntity* loltest = BaseNetworkable::clientEntities()->FindClosest<BaseEntity*>("Landmine", LocalPlayer::Entity(), 3.0f);
			if (loltest && loltest != nullptr)
				loltest->ServerRPC("RPC_Disarm");

			BaseEntity* loltest2 = BaseNetworkable::clientEntities()->FindClosest<BaseEntity*>("BearTrap", LocalPlayer::Entity(), 3.0f);
			if (loltest2 && loltest2 != nullptr)
				loltest2->ServerRPC("RPC_PickupStart");
		}

		if (funcs::localplayer::silentfarm) {

			BaseMelee* melee = LocalPlayer::Entity()->GetHeldEntity<BaseMelee>();
			auto classname = melee->class_name( );
			auto jackhammerorchainsaw = LocalPlayer::Entity()->GetHeldEntity();
			auto classnamej = jackhammerorchainsaw->class_name( );
			if (melee && melee != nullptr && math::m_strcmp(classname, "BaseMelee") ||
				jackhammerorchainsaw && jackhammerorchainsaw != nullptr && math::m_strcmp(classnamej, "Jackhammer") ||
				jackhammerorchainsaw && jackhammerorchainsaw != nullptr && math::m_strcmp(classnamej, "Chainsaw") )
			{
				if ( !math::m_strcmp(classnameheld, "Planner") && !math::m_strcmp(classnameheld, "Hammer") )
				{
					BaseNetworkable* marker = BaseNetworkable::clientEntities()->FindClosest("OreHotSpot", LocalPlayer::Entity(), melee->maxDistance() + 1.8f);
					if (marker && marker != nullptr && marker->IsValid() && marker->transform()->position().distance(LocalPlayer::Entity()->eyes()->position()) <= melee->maxDistance() + 1.8f)
					{
						if (!melee->HasAttackCooldown())
						{
							Vector3 origin = LocalPlayer::Entity()->eyes()->position();
							Vector3 playerPos = marker->transform()->position();
							HitTest* hit = HitTest::New();
							hit->HitEntity() = marker;
							hit->DidHit() = true;
							hit->MaxDistance() = melee->maxDistance();
							hit->HitTransform() = marker->transform();
							hit->AttackRay() = Ray(origin, origin + (playerPos - origin));
							hit->HitNormal() = marker->transform()->InverseTransformPoint(marker->transform()->position());
							hit->HitPoint() = marker->transform()->InverseTransformPoint(marker->transform()->position());
							melee->DoAttack(hit);
							melee->StartAttackCooldown(melee->repeatDelay());
						}
					}
					BaseNetworkable* TreeEntity = TreeEntity = BaseNetworkable::clientEntities()->FindClosest("TreeEntity", LocalPlayer::Entity(), melee->maxDistance() + 1.8f);
					if (TreeEntity && TreeEntity != nullptr && TreeEntity->IsValid() && TreeEntity->transform()->position().distance(LocalPlayer::Entity()->eyes()->position()) <= melee->maxDistance() + 1.8f)
					{
						BaseNetworkable* tree = tree = BaseNetworkable::clientEntities()->FindClosest("TreeMarker", LocalPlayer::Entity(), melee->maxDistance() + 1.8f);
						if (tree && tree != nullptr && tree->IsValid() && tree->transform()->position().distance(LocalPlayer::Entity()->eyes()->position()) <= melee->maxDistance() + 1.8f)
						{
							if (!melee->HasAttackCooldown())
							{
								Vector3 origin = LocalPlayer::Entity()->eyes()->position();
								Vector3 treepos = TreeEntity->transform()->position();
								treepos.y = origin.y;
								HitTest* hit = HitTest::New();
								hit->HitEntity() = TreeEntity;
								hit->DidHit() = true;
								hit->HitMaterial() = System::String::New(xorstr_("Wood"));
								hit->MaxDistance() = melee->maxDistance();
								hit->HitTransform() = TreeEntity->transform();
								hit->AttackRay() = Ray(origin, origin + (treepos - origin));
								hit->HitNormal() = TreeEntity->transform()->InverseTransformPoint(treepos);
								hit->HitPoint() = TreeEntity->transform()->InverseTransformPoint(treepos);
								melee->DoAttack(hit);
								melee->StartAttackCooldown(melee->repeatDelay());
							}
						}
					}
				}
			}

		}

		Vector3 vector = (plly->lastSentTick()->position() + plly->transform()->position()) * 0.5f;
		if (!plly->OnLadder() && !WaterLevel::Test(vector - Vector3(0.0f, 1.85f, 0.0f), true, false, plly)) {
			float num5 = Mathf::Max((flyhackPauseTime > 0.0f) ? 10.0f : 1.0f, 0.0f);
			float num6 = ((plly->GetJumpHeight() + num5) * 3);
			VMaxFlyhack = num6;
			float num7 = Mathf::Max((flyhackPauseTime > 0.0f) ? 10.0f : 1.0f, 0.0f);
			float num8 = ((3.f + num7) * 3);
			HMaxFlyhack = num8;
		}
		/*if (funcs::localplayer::aspect) {
			aspect_ratio();
		}
		if (!funcs::localplayer::aspect){
			antiaspect_ratio();
		}*/
		plly->ClientInput(state);
		if (funcs::localplayer::suicide && GetAsyncKeyState(funcs::localplayer::die)) {
			LocalPlayer::Entity()->OnLand(-108.0001f);
		}
		bool flag7 = target_ply->playerModel()->isNpc();
		bool flag2 = target_ply->HasPlayerFlag(PlayerFlags::Sleeping);
		bool flag3 = target_ply->HasPlayerFlag(PlayerFlags::Wounded);
		bool flag4 = target_ply->mounted();
		if ((flag7 || flag2 || flag3 || flag4)) bigBulletSize = 4;
		if (!flag7 && !flag2 && !flag3 && !flag4) bigBulletSize = 2.69;

		if ( funcs::localplayer::movementline )
		{
			static Vector3 previousPos;
			Vector3 localpos = LocalPlayer::Entity( )->playerModel( )->position( );
			if ( !previousPos.empty( ) )
			{
				if ( LineOfSight(localpos, previousPos) )
					DDraw::Line(Vector3(localpos.x, localpos.y + 0.3f, localpos.z), Vector3(previousPos.x, previousPos.y + 0.3f, previousPos.z), Color(funcs::localplayer::movementlinecol[0], funcs::localplayer::movementlinecol[1], funcs::localplayer::movementlinecol[2], 1), 1.f, true, true);
			}
			previousPos = localpos;
		}
		if (funcs::weapon::meleeradius)
		{
			Vector3 objectcenter = LocalPlayer::Entity()->playerModel()->position();
			BaseMelee* se1x = LocalPlayer::Entity()->GetHeldEntity<BaseMelee>();
			auto classnamese1x = se1x->class_name( );
			int radius = se1x->maxDistance() + 3;
			if (se1x && se1x != nullptr && math::m_strcmp(classnamese1x, "BaseMelee") )
			{
				auto activeWeaponID = LocalPlayer::Entity()->GetActiveWeapon()->GetID();
				if (activeWeaponID != 795236088 && activeWeaponID != 200773292 && activeWeaponID != 1525520776)
				{
					int diameter = 2 * radius;
					double rotationAngle = ImGui::GetTime() * 50.0;

					for (int i = 0; i <= diameter; i++) {
						for (int j = 0; j <= diameter; j++) {
							int distanceX = abs(j - radius);
							int distanceY = abs(i - radius);
							int distanceX1 = abs(j + radius);
							int distanceY1 = abs(i + radius);
							double distance = sqrt(distanceX * distanceX + distanceY * distanceY);

							if (distance == radius - 1) {
								Point center = { radius * 2, radius * 2 };
								Point point = { distanceX1, distanceY1 };
								int curpos = radius * 2;
								std::vector<Point> rotatedPoints;

								for (int angle = 0; angle <= 90; angle += 5) {
									Point rotatedPoint = rotatePointxx(point, center, angle + rotationAngle); // Add rotationAngle to the angle
									rotatedPoints.push_back(rotatedPoint);
								}
								if (funcs::weapon::meleeradiustype == 0)
								{
									for (int i = 0; i < rotatedPoints.size() - 10; i++) {
										float transparency = static_cast<float>(i) / (rotatedPoints.size() - 2);
										Color lineColor(255.f, 255.f, 255.f, transparency * 255);
										DDraw::Line(Vector3(rotatedPoints[i].x + objectcenter.x - curpos, objectcenter.y + 1.0f, rotatedPoints[i].y + objectcenter.z - curpos), Vector3(rotatedPoints[i + 1].x + objectcenter.x - curpos, objectcenter.y + 1.0f, rotatedPoints[i + 1].y + objectcenter.z - curpos), lineColor, 0.001f, false, true);
									}
								}
								if (funcs::weapon::meleeradiustype == 1)
								{
									for (int i = 0; i < rotatedPoints.size() - 1; i++) {
										float transparency = static_cast<float>(i) / (rotatedPoints.size() - 2);
										Color lineColor(transparency * 255.f, transparency * 255.f, transparency * 255.f, transparency);
										DDraw::Line(Vector3(rotatedPoints[i].x + objectcenter.x - curpos, objectcenter.y + 1.0f, rotatedPoints[i].y + objectcenter.z - curpos), Vector3(rotatedPoints[i + 1].x + objectcenter.x - curpos, objectcenter.y + 1.0f, rotatedPoints[i + 1].y + objectcenter.z - curpos), lineColor, 0.001f, false, true);
									}
								}
								if (funcs::weapon::meleeradiustype == 2)
								{
									for (int i = 0; i < rotatedPoints.size() - 1; i++) {
										float hue = static_cast<float>(i) / (rotatedPoints.size() - 2);
										ImColor imColor1 = ImColor::HSV(hue, 1.0f, 1.0f);
										float r1 = imColor1.Value.x;
										float g1 = imColor1.Value.y;
										float b1 = imColor1.Value.z;

										Color lineColor = Color(r1 * 255, g1 * 255, b1 * 255, 255.f);
										DDraw::Line(Vector3(rotatedPoints[i].x + objectcenter.x - curpos, objectcenter.y + 1.0f, rotatedPoints[i].y + objectcenter.z - curpos), Vector3(rotatedPoints[i + 1].x + objectcenter.x - curpos, objectcenter.y + 1.0f, rotatedPoints[i + 1].y + objectcenter.z - curpos), lineColor, 0.001f, false, true);
									}
								}
							}
						}
					}
				}
			}
		}
		if (funcs::localplayer::modelstate)
		{
			switch (funcs::localplayer::modelstatetype)
			{
			case 0:
				LocalPlayer::Entity()->modelState()->flags() |= (int)ModelState::Flags::OnLadder;
				break;
			case 1:
				LocalPlayer::Entity()->modelState()->flags() |= (int)ModelState::Flags::Ducked;
				break;
			case 2:
				LocalPlayer::Entity()->modelState()->flags() |= (int)ModelState::Flags::OnGround;
				break;
			}
		}

		if (funcs::other::acrestrict == 1) {
			RaycastHit hit;
			auto raycast = Physics::RaycastG(LocalPlayer::Entity()->BonePosition(spine2), Vector3::Down(), &hit, 20.f);
			if (raycast)
			{
				if (math::_3distance(hit.point, LocalPlayer::Entity()->BonePosition(spine2)) > 3.5f /*&& math::_3distance(hit.point, LocalPlayer::Entity()->BonePosition(spine3)) < 5.f*/)
				{
					printf("XAntiCheat FLY Bypassed\n");
					if (iarr2 % 2 == 0)
					    LocalPlayer::Entity()->add_modelstate_flag(ModelState::Flags::Mounted);
					else
						LocalPlayer::Entity()->remove_modelstate_flag(ModelState::Flags::Mounted);
					iarr2 += 1;
					

				}

			}
		}

		if (funcs::localplayer::interactivedebug && GetAsyncKeyState(funcs::localplayer::interactivedebugkey))
			LocalPlayer::Entity()->add_modelstate_flag(ModelState::Flags::Mounted);

		if (funcs::localplayer::nosprintrestriction)
		{
			LocalPlayer::Entity()->add_modelstate_flag(ModelState::Flags::Sprinting);
		}
	}
}

inline float GetRandomVelocity_hk(ItemModProjectile* self) noexcept {
	float modifier = 1.0f;
	__try
	{
		if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return self->GetRandomVelocity();
		if (funcs::weapon::lowvelocity)
			modifier = funcs::weapon::bulletspeed;
	}
	__except (true)
	{
	}
	return self->GetRandomVelocity() * modifier;
}
bool donthit = false;


inline void DoMovement_hk(Projectile* projectile, float deltaTime) {
	if (projectile->isAuthoritative() && projectile->isAlive())
	{
		auto currentVelocity = projectile->currentVelocity() * deltaTime;
		auto intmag = currentVelocity.Magnitude();
		auto intnum = 1.f / intmag;
		auto speed = currentVelocity * intnum;
		auto lineposition = projectile->currentPosition() + speed * currentVelocity.Magnitude();
		if (funcs::weapon::bullettracer)
		{
			DDraw::Line(projectile->currentPosition(), lineposition, Color(funcs::weapon::bullettracercol[0], funcs::weapon::bullettracercol[1], funcs::weapon::bullettracercol[2], 1), 1.5f, false, true);
		}

		/*if (funcs::weapon::bulletteleport)
		{
			BasePlayer* projectileTarget = target_ply;
			Transform* playerTransform = projectileTarget->GetTransform(AimSpotInt);
			HitTest* hitTest = projectile->hitTest();

			Vector3 playerPos = playerTransform->position();

			Vector3 bulletPos = projectile->currentPosition();
			Vector3 nextBulletPos = projectile->currentPosition() + (projectile->currentVelocity() * Time::fixedDeltaTime());

			Line updateLine = Line(bulletPos, nextBulletPos);
			Vector3 closestUpdateToPlayer = updateLine.ClosestPoint(playerPos);

			Vector3 yplayerPos;

			if (closestUpdateToPlayer.y - 1 > playerTransform->position().y)
				yplayerPos = playerTransform->position() - Vector3(0, 0.2, 0);
			else
				yplayerPos = playerTransform->position();

			float distanceToPlayer = closestUpdateToPlayer.distance(yplayerPos);

			Vector3 newBulletPos = Vector3_::MoveTowards(closestUpdateToPlayer, playerPos, 0.99f);
			Vector3 newBulletPosx2 = Vector3_::MoveTowards(newBulletPos, playerPos, 0.99f);

			if (distanceToPlayer < bigBulletSize)
			{
				Vector3 pointStart = newBulletPos;
				Vector3 vector = newBulletPosx2;
				vector -= projectile->currentVelocity().normalized() * 0.001f;
				Vector3 vector2 = vector;
				Vector3 b2 = (pointStart - closestUpdateToPlayer).normalized() * AntiHackProtection::projectile_backtracking;
				Vector3 b3 = (vector2 - pointStart).normalized() * AntiHackProtection::projectile_backtracking;

				if (LineOfSight(bulletPos, closestUpdateToPlayer) && LineOfSight(closestUpdateToPlayer, playerPos) &&
					LineOfSight(closestUpdateToPlayer - b2, pointStart + b2) &&
					LineOfSight(pointStart - b3, vector2) &&
					LineOfSight(vector2, vector))
				{
					PlayerProjectileUpdate* ppu = PlayerProjectileUpdate::New();
					if (ppu && hitTest && playerTransform && projectileTarget)
					{
						if (projectile->projectileID() != NULL)
						{
							Vector3 velocityPerTick = projectile->currentVelocity() * Time::fixedDeltaTime();
							float velocityPerTickSpeed = velocityPerTick.Length();
							float speedPerSecond = 1.f / velocityPerTickSpeed;
							float distanceTraveled = (closestUpdateToPlayer - bulletPos).Length();
							float traveledTime = distanceTraveled * speedPerSecond * Time::fixedDeltaTime();
							projectile->traveledDistance() += distanceTraveled;
							projectile->traveledTime() += traveledTime;
							ppu->projectileId() = projectile->projectileID();
							ppu->travelTime() = projectile->traveledTime() + traveledTime;
							ppu->curVelocity() = projectile->currentVelocity();
							ppu->curPosition() = closestUpdateToPlayer;
							LocalPlayer::Entity()->SendProjectileUpdate(ppu);
							ppu->curPosition() = newBulletPos;
							LocalPlayer::Entity()->SendProjectileUpdate(ppu);
							hitTest->DidHit() = true;
							hitTest->HitEntity() = projectileTarget;
							hitTest->HitTransform() = playerTransform;
							hitTest->HitPoint() = playerTransform->InverseTransformPoint(newBulletPosx2);
							hitTest->HitNormal() = playerTransform->InverseTransformDirection(newBulletPosx2);
							hitTest->AttackRay() = Ray(newBulletPos, Vector3());
							hitTest->HitMaterial() = System::String::New(xorstr_("Flesh"));
							if (projectile->projectileID() != 0 && ppu->projectileId() != 0 && check_hit(newBulletPosx2, projectile))
							{
								projectile->DoHit(hitTest, newBulletPosx2, Vector3());
								DDraw::Capsule(closestUpdateToPlayer, Quaternion(), 0.3f, 2 * 0.3f, Color(1, 1, 1, 1), 5.f, false, true);
							}
							projectile->swimRandom( ) = 0.f;
							projectile->swimScale( ) = Vector3(0.f, 0.f, 0.f);
							projectile->swimSpeed( ) = Vector3(0.f, 0.f, 0.f);
						}
					}
				}
			}
		}*/

		if ( funcs::weapon::bulletteleport )
		{
			BasePlayer* projectileTarget = target_ply;
			
			Transform* playerTransform = projectileTarget->GetTransform(AimSpotInt);
			HitTest* hitTest = projectile->hitTest( );

			Vector3 playerPos = playerTransform->position( );

			Vector3 bulletPos = projectile->currentPosition( );
			Vector3 nextBulletPos = projectile->currentPosition( ) + ( projectile->currentVelocity( ) * Time::fixedDeltaTime( ) );

			Line updateLine = Line(bulletPos, nextBulletPos);
			Vector3 closestUpdateToPlayer = updateLine.ClosestPoint(playerPos);

			Vector3 yplayerPos;

			if ( closestUpdateToPlayer.y - 1 > playerTransform->position( ).y )
				yplayerPos = playerTransform->position( ) - Vector3(0, 0.2, 0);
			else
				yplayerPos = playerTransform->position( );

			float distanceToPlayer = closestUpdateToPlayer.distance(yplayerPos);

			Vector3 newBulletPos = Vector3_::MoveTowards(closestUpdateToPlayer, playerPos, 0.99f);
			Vector3 newBulletPosx2 = Vector3_::MoveTowards(newBulletPos, playerPos, 0.99f);


			if ( distanceToPlayer < bigBulletSize )
			{
				Vector3 pointStart = newBulletPos;
				Vector3 vector = newBulletPosx2;
				vector -= projectile->currentVelocity( ).normalized( ) * 0.001f;
				Vector3 vector2 = vector;
				Vector3 b2 = ( pointStart - closestUpdateToPlayer ).normalized( ) * AntiHackProtection::projectile_backtracking;
				Vector3 b3 = ( vector2 - pointStart ).normalized( ) * AntiHackProtection::projectile_backtracking;

				if ( LineOfSight(bulletPos, closestUpdateToPlayer) && LineOfSight(closestUpdateToPlayer, playerPos) &&
					LineOfSight(closestUpdateToPlayer - b2, pointStart + b2) &&
					LineOfSight(pointStart - b3, vector2) &&
					LineOfSight(vector2, vector) )
				{
					PlayerProjectileUpdate* ppu = PlayerProjectileUpdate::New( );
					if ( ppu && hitTest && playerTransform && projectileTarget )
					{
						if ( projectile->projectileID( ) != NULL )
						{
							Vector3 velocityPerTick = projectile->currentVelocity( ) * Time::fixedDeltaTime( );
							float velocityPerTickSpeed = velocityPerTick.Length( );
							float speedPerSecond = 1.f / velocityPerTickSpeed;
							float distanceTraveled = ( closestUpdateToPlayer - bulletPos ).Length( );
							float traveledTime = distanceTraveled * speedPerSecond * Time::fixedDeltaTime( );
							projectile->traveledDistance( ) += distanceTraveled;
							projectile->traveledTime( ) += traveledTime;
							ppu->projectileId( ) = projectile->projectileID( );
							ppu->travelTime( ) = projectile->traveledTime( ) + traveledTime;
							ppu->curVelocity( ) = projectile->currentVelocity( );
							ppu->curPosition( ) = closestUpdateToPlayer;
							LocalPlayer::Entity( )->SendProjectileUpdate(ppu);
							ppu->curPosition( ) = newBulletPos;
							LocalPlayer::Entity( )->SendProjectileUpdate(ppu);
							hitTest->DidHit( ) = true;
							hitTest->HitEntity( ) = projectileTarget;
							hitTest->HitTransform( ) = playerTransform;
							hitTest->HitPoint( ) = playerTransform->InverseTransformPoint(newBulletPosx2);
							hitTest->HitNormal( ) = playerTransform->InverseTransformDirection(newBulletPosx2);
							hitTest->AttackRay( ) = Ray(newBulletPos, Vector3( ));
							hitTest->HitMaterial( ) = System::String::New(xorstr_("Flesh"));
							if ( projectile->projectileID( ) != 0 && ppu->projectileId( ) != 0 && check_hit(newBulletPosx2, projectile) )
							{
								projectile->DoHit(hitTest, newBulletPosx2, Vector3( ));
								DDraw::Capsule(closestUpdateToPlayer, Quaternion( ), 0.3f, 2 * 0.3f, Color(1, 1, 1, 1), 5.f, false, true);
							}
						}
					}
				}
			}
		}

		Vector3 bulletPos = projectile->currentPosition();
		Vector3 nextBulletPos = projectile->currentPosition() + (projectile->currentVelocity() * Time::fixedDeltaTime());
		if (LineOfSight(bulletPos, nextBulletPos)) donthit = true;
		else donthit = false;
	}
	
	return projectile->DoMovement(deltaTime);
}
inline void Launch_hk(Projectile* prdoj) {

	//Vector3 eyes_position = LocalPlayer::Entity( )->eyes( )->position( );
	//Vector3 object_position = MainCamera::Camera( )->Get_Position( );
	//Vector3 position_offset = object_position - eyes_position;
	//float magnitude = position_offset.magnitude( );
	//char buffer[50];
	//sprintf( buffer, "%f", magnitude );
	//LocalPlayer::Entity( )->consolemsg( System::String::New( buffer ) );

	return prdoj->Launch();
}
inline void AddPunch_hk(HeldEntity* attackEntity, Vector3 amount, float duration) noexcept {
	Vector3 amount_new;
	__try
	{
		if (funcs::weapon::recoilas) amount_new = amount * (funcs::weapon::norecoil / 100.0f);
		else amount_new = amount;

		LocalPlayer::Entity()->input()->state()->current()->aimAngles() += (amount - amount_new);
	}
	__except (true)
	{
	}
	attackEntity->AddPunch(amount_new, duration);
}

inline Vector3 MoveTowards_hk(Vector3 current, Vector3 target, float maxDelta) {
	if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return Vector3_::MoveTowards(current, target, maxDelta);
	static auto ptr = METHOD("Assembly-CSharp::BaseProjectile::SimulateAimcone(): Void");
	if (!ptr) return Vector3_::MoveTowards(current, target, maxDelta);
	if (CALLED_BY(ptr, 0x800)) {
		if (funcs::weapon::recoilas)
		{
			target *= funcs::weapon::norecoil / 100.0f;
			maxDelta *= funcs::weapon::norecoil / 100.0f;
		}
		else
		{
			target *= 1;
			maxDelta *= 1;
		}
	}
	return Vector3_::MoveTowards(current, target, maxDelta);
}
inline bool DoHit_hk(Projectile* prj, HitTest* test, Vector3 point, Vector3 normal) noexcept {
	__try
	{
		//LocalPlayer::Entity( )->consolemsg(test->HitMaterial( ));
		if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) 	return prj->DoHit(test, point, normal);
		if (funcs::weapon::pierce) {
			if (prj->isAuthoritative()) {
				auto lol = test->HitEntity();
				auto classname = lol->class_name( );
				if (donthit && !math::m_strcmp(classname, "BasePlayer") && !math::m_strcmp(classname, "BaseAnimalNPC") && !math::m_strcmp(classname, "Boar") &&
					!math::m_strcmp(classname, "Bear") && !math::m_strcmp(classname, "Wolf") ) return false;
			}
		}
	}
	__except (true)
	{
	}
	return prj->DoHit(test, point, normal);
}

inline System::String* ConsoleRun_hk(ConsoleSystem::Option* optiom, System::String* str, Array<System::Object_*>* args) noexcept {
	if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) 	return ConsoleSystem::Run(optiom, str, args);
		if (optiom->IsFromServer()) {
			if (str->buffer) {
				auto string = std::wstring(str->buffer);
				if (string.find(xorstr_(L"noclip")) != std::wstring::npos ||
					string.find(xorstr_(L"debugcamera")) != std::wstring::npos ||
					string.find(xorstr_(L"admintime")) != std::wstring::npos ||
					string.find(xorstr_(L"culling.debug")) != std::wstring::npos ||
					string.find(xorstr_(L"camlerp")) != std::wstring::npos ||
					string.find(xorstr_(L"camspeed")) != std::wstring::npos) {
	
					str = System::String::New(xorstr_(""));
				}
			}
		}
	return ConsoleSystem::Run(optiom, str, args);
}

inline void Load_hk(BasePlayer* self, BaseNetworkable::LoadInfo* info) noexcept
{
	__try
	{
		if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) 	return self->Load(info);
		if (info->msg->basePlayer() != nullptr)
		{
			auto basePlayer = info->msg->basePlayer();
			if (basePlayer->userid() == LocalPlayer::Entity()->userID())
				funcs::localplayer::istrueadmin = basePlayer->HasPlayerFlag(PlayerFlags::IsAdmin);
		}
	}
	__except (true)
	{
	}
	return self->Load(info);
}

inline void Loadbc_hk(BasePlayer* self, BaseNetworkable::LoadInfo* info)
{
	if (info->msg->baseCombat() != nullptr)
	{
		/*self->health() = info->msg->baseCombat()->health();*/
		printf("%f\n", info->msg->baseCombat()->health());
	}
}



inline void set_flying_hk(ModelState* modelState, bool state) noexcept {
	__try
	{
		if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return modelState->set_flying(state);
		if (funcs::localplayer::istrueadmin)
			return modelState->set_flying(state);
	}
	__except (true)
	{
	}
	return modelState->set_flying(false);
}

inline void UpdateAmbientHook(TOD_Sky* sky) noexcept
{
	__try
	{
		if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected) || !funcs::localplayer::ambient) return sky->UpdateAmbient();
		TOD_Sky::set_ambientMode(TOD_Sky::AmbientMode::Flat);
		TOD_Sky::set_ambientIntensity(6.f);
		TOD_Sky::set_ambientLight(Color({ funcs::visuals::ambientcolor[0], funcs::visuals::ambientcolor[1], funcs::visuals::ambientcolor[2], 1 }));
		/*TOD_Sky::set_skybox(skybox);*/

	}
	__except (true)
	{
	}
}

inline void set_skybox(RenderSettings* sky) noexcept
{
	__try
	{
		if ( LocalPlayer::Entity( )->HasPlayerFlag(PlayerFlags::Spectating) || !funcs::localplayer::ambient ) return sky->set_skybox( );

	}
	__except ( true )
	{
	}
}



inline void UpdateRenderSettingsHook(TOD_Sky* sky) noexcept
{
	__try
	{
		if ( !LocalPlayer::Entity( )->HasPlayerFlag(PlayerFlags::Connected) || !funcs::localplayer::ambient ) return sky->UpdateRenderSettings( );
		TOD_Sky::set_skybox(skybox);

	}
	__except ( true )
	{
	}
}


bool TestFlying2(BasePlayer* ply = LocalPlayer::Entity(),
	Vector3 oldPos = Vector3::Zero(),
	Vector3 newPos = Vector3::Zero(),
	bool verifyGrounded = true)
{
	bool isInAir = false;
	if (verifyGrounded)
	{
		auto extrusion = 2.f;
		Vector3 vec = (oldPos + newPos) * 0.5f;
		auto margin = 0.05f;
		float radius = ply->GetRadius();
		float height = ply->GetHeight();
		Vector3 vec2 = vec + Vector3(0.f, radius - extrusion, 0.f);
		Vector3 vec3 = vec + Vector3(0.f, height - radius, 0.f);
		float radius2 = radius - margin;
		isInAir = !GamePhysics::CheckCapsule(vec2, vec3, radius2, 1503731969, GamePhysics::QueryTriggerInteraction::Ignore);

		if (isInAir)
		{
			bool flag = false;
			Vector3 vec4 = newPos - oldPos;
			float num2 = std::fabs(vec4.y);
			float num3 = vec4.Magnitude();

			if (vec4.y >= 0.f)
			{
				flag = true;
				flyhackDistanceVertical += vec4.y;
			}

			if (num2 < num3)
			{
				flag = true;
				flyhackDistanceHorizontal += num3;
			}

			if (flag)
			{
				float num4 = Mathf::Max((flyhackPauseTime > 0.f ? 10.f : 1.5f), 0.f);
				float num5 = ply->GetJumpHeight() + num4;
				if (flyhackDistanceVertical > num5)
				{
					return true;
				}

				float num6 = num4;
				float num7 = 5.f + num6;
				if (flyhackDistanceHorizontal > num7)
				{
					return true;
				}
			}
		}
		else
		{
			flyhackDistanceVertical = 0.0f;
			flyhackDistanceHorizontal = 0.0f;
		}
	}
	return false;
}

bool ValidateMove(float deltaTime)
{
	auto lp = LocalPlayer::Entity();

	bool result;
	bool flag = deltaTime > 1.0f;

	//test for flying
	flyhackPauseTime = Mathf::Max(0.f, flyhackPauseTime - deltaTime);
	ticks.Reset();
	if (ticks.HasNext())
	{
		bool flag = lp->transform() ? !(!lp->transform()) : false;

		Matrix matrix4x = flag ? Matrix::identityMatrix() :
			lp->transform()->get_localToWorldMatrix();

		Vector3 oldPos = flag ? ticks.startPoint :
			matrix4x.MultiplyPoint3x4(ticks.startPoint);
		Vector3 vector = flag ? ticks.startPoint :
			matrix4x.MultiplyPoint3x4(ticks.endPoint);
		float num = 0.1f;
		float num2 = 15.0f;
		num = Mathf::Max(ticks.len / num2, num);
		while (ticks.MoveNext(num))
		{
			vector = (flag ? ticks.currentPoint
				: matrix4x.MultiplyPoint3x4(ticks.currentPoint));

			TestFlying2(lp, oldPos, vector, true);
			oldPos = vector;
		}
	}
	return true;
}

void FinalizeTick(float deltaTime)
{
	tickDeltaTime += deltaTime;
	bool flag = ticks.startPoint != ticks.endPoint;
	if (flag)
	{
		if (ValidateMove(tickDeltaTime)
			&& funcs::flyhack::flyhackindicator || funcs::flyhack::antiflyhack)
		{
			//printf("GOOD\n");
		}
		else
		{
			//printf("BAD\n");
		}
		funcs::flyhack::flyhackfloat = flyhackDistanceVertical;
		funcs::flyhack::hor_flyhack = flyhackDistanceHorizontal;
	}
	ticks.Reset(LocalPlayer::Entity()->transform()->position());
}

void ServerUpdate(float deltaTime, BasePlayer* ply)
{
	float timeSinceLastTick = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime());
	desyncTimeRaw = Mathf::Max(timeSinceLastTick - deltaTime, 0.f);
	desyncTimeClamped = Mathf::Min(desyncTimeRaw, 1.f);
	FinalizeTick(deltaTime);
}

inline void SendClientTickHook(BasePlayer* player) noexcept
{
		__try
		{
			if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) 	return player->SendClientTick();
			if (player->userID() == LocalPlayer::Entity()->userID()) {
				Vector3 current = player->transform()->position();
				Vector3 old = player->lastSentTick()->position();
				Vector3 vector4 = (player->transform()->position() - player->lastSentTick()->position());
				Vector3 overrided = Vector3(current.x, current.y, current.z);
			
				if (funcs::flyhack::antiflyhack && funcs::flyhack::flyhackfloat >= 3.0f &&
					!GetAsyncKeyState(funcs::localplayer::ignoreanyfly))
				{
					overrided = Vector3(overrided.x, current.y < old.y ? (current.y - 0.3f) : old.y, overrided.z);
				}
				if (funcs::flyhack::antiflyhack && funcs::flyhack::hor_flyhack >= 4.6f &&
					!GetAsyncKeyState(funcs::localplayer::ignoreanyfly))
				{
					overrided = Vector3(old.x, overrided.y, old.z);
				}
				if (funcs::flyhack::antiflyhack && funcs::flyhack::hor_flyhack >= 4.5f || funcs::flyhack::antiflyhack && funcs::flyhack::flyhackfloat >= 3.0f)
				{
					if (overrided != current)
						player->movement()->TeleportTo(overrided);
				}

				if (funcs::localplayer::bhop && GetAsyncKeyState(funcs::localplayer::bhopkey) ||
					funcs::localplayer::bhop && funcs::localplayer::bhopkey == 0)
				{
					static float b = 4.0f;
					if (b >= 4.0f)
					{
						float radius = player->GetRadius();
						float height = player->GetHeight(false);
						Vector3 vector = (player->lastSentTick()->position() + player->transform()->position()) * 0.5f;
						float flyhack_extrusion = 0.25f;
						Vector3 vector2 = vector + Vector3(0.0f, radius - flyhack_extrusion, 0.0f);
						Vector3 vector3 = vector + Vector3(0.0f, height - radius, 0.0f);
						float radius2 = radius - 0.05f;
						bool isgrounded = GamePhysics::CheckCapsule(vector2, vector3, radius2, 1503731969, GamePhysics::QueryTriggerInteraction::Ignore);
						if (isgrounded) {
							player->movement()->Jump(player->modelState());
							b = 0.0f;
						}
					}
					b++;
				}
				if (funcs::localplayer::antiaim)
				{
					player->input()->state()->current()->aimAngles() = Vector3(-999, rand() % 999, rand() % 999);
				}
				cLastTickPos = player->transform()->position();
				ticks.AddPoint(cLastTickPos);

				if (funcs::flyhack::flyhackindicator || funcs::flyhack::antiflyhack)
				{
					ServerUpdate(tickDeltaTime, player);
				}
			}
		}
		__except (true)
		{
		}
		return player->SendClientTick();
		
}

void CursorManagerUpdate_hk(CursorManager* _this)
{
	if ( !menu::menuopen ) return _this->Update( );
	
	CursorManager::set_visible(true);
	CursorManager::set_lockstate(0);
	
}

void UIPaintableImage_hk(UIPaintableImage* _this)
{


}

void DoHitNotify_hk(BaseCombatEntity* entity, HitInfo* info, Projectile* prj) {
	__try
	{
		if (entity->IsPlayer()) {
			float damage = info->damageTypes()->Total();
			hitmarker::d_indicator_t DmgIndicator;
			DmgIndicator.damage = damage;
			DmgIndicator.player = reinterpret_cast<BasePlayer*>(entity);
			DmgIndicator.hit_box = head;
			DmgIndicator.erase_time = Time::time() + 3.2;
			DmgIndicator.initialized = false;
			hitmarker::get().d_indicators.push_back(DmgIndicator);
			hitmarker::get().add_hit(hitmarker_t(Time::time(), damage, head, reinterpret_cast<BasePlayer*>(entity)->BonePosition(head)));

			if (funcs::weapon::customhitsound) {
				PlaySoundA((LPCSTR)NL, NULL, SND_MEMORY | SND_ASYNC);
				return;
			}
		}
	}
	__except (true)
	{
	}
	return entity->DoHitNotify(entity, info, prj);
}
GameObject* CreateEffect_hk(pUncStr strPrefab, Effect* effect)
{
	auto effectName = strPrefab->str;
	Vector3 position = effect->worldPos();
	if (funcs::objects::raidesp)
	{
		if ( effect && strPrefab->str && !position.empty( ) ) {
			switch ( RUNTIME_CRC32_W(effectName) ) {
			case STATIC_CRC32("assets/prefabs/tools/c4/effects/c4_explosion.prefab"):
				LogSystem::LogExplosion(xorstr_("C4"), position);
				break;
			case STATIC_CRC32("assets/prefabs/weapons/satchelcharge/effects/satchel-charge-explosion.prefab"):
				LogSystem::LogExplosion(xorstr_("Satchel"), position);
				break;
			case STATIC_CRC32("assets/prefabs/weapons/rocketlauncher/effects/rocket_explosion_incendiary.prefab"):
				LogSystem::LogExplosion(xorstr_("Incendiary rocket"), position);
				break;
			case STATIC_CRC32("assets/prefabs/weapons/rocketlauncher/effects/rocket_explosion.prefab"):
				LogSystem::LogExplosion(xorstr_("Rocket"), position);
				break;
			}
		}

	}
	return EffectLibrary::CreateEffect_(strPrefab, effect);
}

inline void ProcessAttack_hk(BaseMelee* self, HitTest* hit) noexcept {
	__try
	{
		BaseNetworkable* entity = entity = hit->HitEntity();
		bool is_team = reinterpret_cast<BasePlayer*>(entity)->is_teammate();
		if (is_team) return;
		if (!funcs::localplayer::silentfarm || !entity)
			return self->ProcessAttack(hit);
		auto classname = entity->class_name( );
		if ( math::m_strcmp(classname, "TreeEntity") ) {
			BaseNetworkable* marker = marker = BaseNetworkable::clientEntities()->FindClosest("TreeMarker", entity, 5.0f);
			if (marker && marker != nullptr) {
				hit->HitTransform() = marker->transform();
				hit->HitPoint() = marker->transform()->InverseTransformPoint(marker->transform()->position());
				hit->HitMaterial() = System::String::New(xorstr_("Wood"));
			}
		}
	}
	__except (true)
	{
	}
	return self->ProcessAttack(hit);
}



inline void TerrainHeight_ctor_hk(TerrainHeightMap* map)
{
	__try
	{
		TerrainMap = map;
	}
	__except (true)
	{
	}
	return map->ctor();
}

inline void TerrainMeta_ctor_hk(TerrainMeta* meta)
{
	__try
	{
		Terrainmeta = meta;
	}
	__except (true)
	{
	}
	return meta->ctor();
}

inline void TerrainCollision_ctor_hk(TerrainCollision* col)
{
	__try
	{
		Terraincollision = col;
	}
	__except (true)
	{
	}
	return col->ctor();
}
inline void Terrain_ctor_hk(Terrain* terr)
{
	__try
	{
		terrain = terr;
	}
	__except (true)
	{
	}
	return terr->ctor();
}

void Hk_TryToMove(ItemIcon* a1) {
	__try
	{
		a1->TryToMove();
		if (funcs::localplayer::instaloot) {
			if (a1->queuedForLooting())
			{
				a1->RunTimedAction();
			}
		}
	}
	__except (true)
	{
	}
}
void VisUpdateUsingCulling(BasePlayer* pl, float dist, bool vis) {
	__try
	{
	if (funcs::visuals::chams) {
		return pl->VisUpdateUsingCulling(2.f, true);
	}
	else {
		return pl->VisUpdateUsingCulling(dist, vis);
	}
	}
	__except (true)
	{
		return pl->VisUpdateUsingCulling(dist, vis);
	}
}


inline void do_hooks() {
	//ASSIGN_HOOK("Assembly-CSharp::HitTest::BuildAttackMessage(): Attack", HitTest::BuildAttackMessage_);
	hookengine::hook((void*)METHOD("Assembly-CSharp::EffectLibrary::CreateEffect(String,Effect): GameObject"), (void**)&EffectLibrary::CreateEffect_, CreateEffect_hk);
	//hookengine::hook((void*)(game_assembly + 0x7ED420), (void**)&BasePlayer::Loadbc_, Loadbc_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::Projectile::DoMovement(Single): Void"), (void**)&Projectile::DoMovement_, DoMovement_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::Projectile::Launch(): Void"), (void**)&Projectile::Launch_, Launch_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::TerrainCollision::.ctor(): Void"), (void**)&TerrainCollision::ctor_, TerrainCollision_ctor_hk);
	hookengine::hook((void*)METHOD("UnityEngine.TerrainModule::UnityEngine::Terrain::.ctor(): Void"), (void**)&Terrain::ctor_, Terrain_ctor_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp-firstpass::TOD_Sky::UpdateAmbient(): Void"), (void**)&TOD_Sky::UpdateAmbient_, UpdateAmbientHook);	
	hookengine::hook((void*)METHOD("Assembly-CSharp::TerrainMeta::.ctor(): Void"), (void**)&TerrainMeta::ctor_, TerrainMeta_ctor_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::TerrainHeightMap::.ctor(): Void"), (void**)&TerrainHeightMap::ctor_, TerrainHeight_ctor_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::BasePlayer::SendClientTick(): Void"), (void**)&BasePlayer::SendClientTick_, SendClientTickHook);
	hookengine::hook((void*)METHOD("Assembly-CSharp::BasePlayer::Load(LoadInfo): Void"), (void**)&BasePlayer::Load_, Load_hk);
	//hookengine::hook(( void* ) METHOD("Assembly-CSharp::BaseCombatEntity::Load(LoadInfo): Void"), ( void** ) &BasePlayer::Load2_, loadprank_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::PlayerWalkMovement::UpdateVelocity(): Void"), (void**)&PlayerWalkMovement::UpdateVelocity_, UpdateVelocity_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::PlayerWalkMovement::HandleJumping(ModelState,Boolean,Boolean): Void"), (void**)&PlayerWalkMovement::HandleJumping_, HandleJumping_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::BasePlayer::CanAttack(): Boolean"), (void**)&BasePlayer::CanAttack_, CanAttack_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::BasePlayer::OnLand(Single): Void"), (void**)&BasePlayer::OnLand_, OnLand_hk);
	hookengine::hook(( void* ) METHOD("Assembly-CSharp::FlintStrikeWeapon::DoAttack(): Void"), ( void** ) &FlintStrikeWeapon::DoAttack_, DoAttack_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::FlintStrikeWeapon::DoAttack(): Void"), (void**)&FlintStrikeWeapon::DoAttack_, DoAttack_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::BaseCombatEntity::OnAttacked(HitInfo): Void"), (void**)&BaseCombatEntity::OnAttacked_, OnAttacked_hk);
	hookengine::hook((void*)METHOD("Facepunch.Console::ConsoleSystem::Run(Option,String,Object[]): String"), (void**)&ConsoleSystem::Run_, ConsoleRun_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::BasePlayer::VisUpdateUsingCulling(Single,Boolean): Void"), (void**)&BasePlayer::VisUpdateUsingCulling_, VisUpdateUsingCulling);
	hookengine::hook((void*)METHOD("Assembly-CSharp::Projectile::Update(): Void"), (void**)&Projectile::Update_, ProjectileUpdate_hk);
	hookengine::hook((void*)METHOD("Rust.Data::ModelState::set_flying(Boolean): Void"), (void**)&ModelState::set_flying_, set_flying_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::HitTest::BuildAttackMessage(BaseEntity): Attack"), (void**)&HitTest::BuildAttackMessage_, BuildAttackMessage_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::BaseMelee::ProcessAttack(HitTest): Void"), (void**)&BaseMelee::ProcessAttack_, ProcessAttack_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::Projectile::DoHit(HitTest,Vector3,Vector3): Boolean"), (void**)&Projectile::DoHit_, DoHit_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::BaseMountable::EyePositionForPlayer(BasePlayer,Quaternion): Vector3"), (void**)&BaseMountable::EyePositionForPlayer_, EyePositionForPlayer_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::ItemIcon::TryToMove(Boolean): Void"), (void**)&ItemIcon::StartCoroutine_, Hk_TryToMove);
	hookengine::hook((void*)METHOD("Assembly-CSharp::BasePlayer::ClientInput(InputState): Void"), (void**)&BasePlayer::ClientInput_, ClientInput_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::ItemModProjectile::GetRandomVelocity(): Single"), (void**)&ItemModProjectile::GetRandomVelocity_, GetRandomVelocity_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::PlayerEyes::get_BodyLeanOffset(): Vector3"), (void**)&PlayerEyes::BodyLeanOffset_, BodyLeanOffset_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::AimConeUtil::GetModifiedAimConeDirection(Single,Vector3,Boolean): Vector3"), (void**)&AimConeUtil::GetModifiedAimConeDirection_, GetModifiedAimConeDirection_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::PlayerEyes::DoFirstPersonCamera(Camera): Void"), (void**)&PlayerEyes::DoFirstPersonCamera_, DoFirstPersonCamera_hk);
	hookengine::hook((void*)METHOD("UnityEngine.CoreModule::UnityEngine::Vector3::MoveTowards(Vector3,Vector3,Single): Vector3"), (void**)&Vector3_::MoveTowards_, MoveTowards_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::HeldEntity::AddPunch(Vector3,Single): Void"), (void**)&HeldEntity::AddPunch_, AddPunch_hk);
	hookengine::hook((void*)METHOD("Assembly-CSharp::BaseCombatEntity::DoHitNotify(HitInfo): Void"), (void**)&BaseCombatEntity::DoHitNotify_, DoHitNotify_hk);
	hookengine::hook(( void* ) METHOD("Assembly-CSharp::CursorManager::Update(): Void"), ( void** ) &CursorManager::Update_, CursorManagerUpdate_hk);
	//hookengine::hook(( void* )(game_assembly + 0xAB75B0 ) /*METHOD("Assembly-CSharp::MeshPaintableSource::Load(byte[]): Void")*/, ( void** ) &UIPaintableImage::Update_, UIPaintableImage_hk);
}

