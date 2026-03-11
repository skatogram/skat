#pragma once
namespace AntiHackProtection
{
	static float noclip_margin_dismount = 0.22f;
	static float noclip_backtracking = 0.01f;
	static bool reporting = false;
	static bool admincheat = true;
	static bool objectplacement = true;
	static bool modelstate = true;
	static bool forceposition = true;
	static int userlevel = 2;
	static int enforcementlevel = 1;
	static float maxdesync = 1.f;
	static float maxdeltatime = 1.f;
	static float tickhistorytime = 0.5f;
	static float tickhistoryforgiveness = 0.1f;
	static float relaxationrate = 0.1f;
	static float relaxationpause = 10.f;
	static float maxviolation = 100.f;
	static int terrain_protection = 1;
	static int terrain_timeslice = 64;
	static float terrain_padding = 0.3f;
	static float terrain_penalty = 100.f;
	static bool terrain_kill = true;
	static bool terrain_check_geometry = false;
	static int noclip_protection = 3;
	static bool noclip_reject = true;
	static float noclip_penalty = 0.f;
	static float noclip_margin = 0.09f;
	static float noclip_stepsize = 0.1f;
	static int noclip_maxsteps = 15;
	static int speedhack_protection = 2;
	static bool speedhack_reject = true;
	static float speedhack_penalty = 0.f;
	static float speedhack_forgiveness = 2.f;
	static float speedhack_forgiveness_inertia = 10.f;
	static float speedhack_slopespeed = 10.f;
	static int flyhack_protection = 3;
	static bool flyhack_reject = false;
	static float flyhack_penalty = 100.f;
	static float flyhack_forgiveness_vertical = 1.5f;
	static float flyhack_forgiveness_vertical_inertia = 10.f;
	static float flyhack_forgiveness_horizontal = 1.5f;
	static float flyhack_forgiveness_horizontal_inertia = 10.f;
	static float flyhack_extrusion = 2.f;
	static float flyhack_margin = 0.05f;
	static float flyhack_stepsize = 0.1f;
	static int flyhack_maxsteps = 15;
	static int projectile_protection = 6;
	static float projectile_penalty = 0.f;
	static float projectile_forgiveness = 0.5f;
	static float projectile_serverframes = 2.f;
	static float projectile_clientframes = 2.f;
	static float projectile_trajectory = 1.f;
	static float projectile_anglechange = 60.f;
	static float projectile_velocitychange = 1.1f;
	static float projectile_desync = 1.f;
	static float projectile_backtracking = 0.01f;
	static float projectile_losforgiveness = 0.2f;
	static int projectile_damagedepth = 2;
	static int projectile_impactspawndepth = 1;
	static bool projectile_terraincheck = true;
	static bool projectile_vehiclecheck = true;
	static bool projectile_positionoffset = true;
	static int melee_protection = 4;
	static float melee_penalty = 0.f;
	static float melee_forgiveness = 0.5f;
	static float melee_serverframes = 2.f;
	static float melee_clientframes = 2.f;
	static float melee_backtracking = 0.01f;
	static float melee_losforgiveness = 0.2f;
	static bool melee_terraincheck = true;
	static bool melee_vehiclecheck = true;
	static int eye_protection = 4;
	static float eye_penalty = 0.f;
	static float eye_forgiveness = 0.5f;
	static float eye_serverframes = 2.f;
	static float eye_clientframes = 2.f;
	static bool eye_terraincheck = true;
	static bool eye_vehiclecheck = true;
	static float eye_noclip_cutoff = 0.06f;
	static float eye_noclip_margin = 0.21f;
	static float eye_noclip_backtracking = 0.01f;
	static float eye_losradius = 0.18f;
	static float eye_history_penalty = 100.f;
	static float eye_history_forgiveness = 0.1f;
	static float build_losradius = 0.01f;
	static float build_losradius_sleepingbag = 0.3f;
	static bool build_terraincheck = true;
	static bool build_vehiclecheck = true;
	static int build_inside_check = 2;
	static int debuglevel = 1;
}

float desyncTimeRaw = 0.f;
float desyncTimeClamped = 0.f;
float tickDeltaTime = 0.f;


bool check_hit(Vector3 HitPositionWorld, Projectile* projectile)
{
	bool hit = true;

	if (projectile->integrity() <= 0.f)
	{
		hit = false; //projectile_integrity
	}
	float timeSinceLastTick = ( Time::realtimeSinceStartup( ) - LocalPlayer::Entity( )->lastSentTickTime( ) );
	float last_tick_time = Mathf::Max(0.f, Mathf::Min(timeSinceLastTick, 1.f));
	float magnitude = target_ply->GetParentVelocity().magnitude();
	float num2 = 1.f + AntiHackProtection::projectile_forgiveness;
	float num9 = AntiHackProtection::projectile_clientframes / 60.f;
	float num10 = AntiHackProtection::projectile_serverframes * Mathx::Max(Time::deltaTime(), Time::smoothDeltaTime(), Time::fixedDeltaTime());
	float num12 = ( last_tick_time + num9 + num10) * num2;
	float num14 = projectile->currentPosition().distance(HitPositionWorld) + 0.01;
	float num19 = target_ply->BoundsPadding() + num12 * magnitude + AntiHackProtection::tickhistoryforgiveness;
	float num20 = target_ply->Distance(HitPositionWorld);

	bool flag7 = target_ply->playerModel()->isNpc();
	bool flag2 = target_ply->HasPlayerFlag(PlayerFlags::Sleeping);
	bool flag3 = target_ply->HasPlayerFlag(PlayerFlags::Wounded);
	bool flag4 = target_ply->mounted();


	float num16 = target_ply->MaxVelocity() + target_ply->GetParentVelocity().magnitude();
	float num17 = target_ply->BoundsPadding() + num12 * num16;
	float num18 = target_ply->Distance(HitPositionWorld);
	//if (num18 > num17)
	//{
	//	hit = false; //entity_distance
	//}
	//if (!flag7 && !flag2 && !flag3 && !flag4)
	//{
	//	if (num20 > num19)
	//	{
	//		hit = false; //player_distance
	//	}
	//}
	
	
	float num21 = target_ply->MaxVelocity() + target_ply->GetParentVelocity().magnitude();
	float num22 = num12 * num21;
	float num24 = projectile->traveledDistance() + 1.f + projectile->currentPosition().magnitude() + num22;
	if (num14 > num24)
	{
		hit = false; //projectile_distance
	}
	return hit;
}


bool check_eye(Vector3 eyePos)
{
	
	float timeSinceLastTick = ( Time::realtimeSinceStartup( ) - LocalPlayer::Entity( )->lastSentTickTime( ) );
	float last_tick_time = Mathf::Max(0.f, Mathf::Min(timeSinceLastTick, 1.f));
	bool hit = true;
	float num = 1.f + AntiHackProtection::eye_forgiveness;
	float eye_clientframes = AntiHackProtection::eye_clientframes;
	float eye_serverframes = AntiHackProtection::eye_serverframes;
	float num2 = eye_clientframes / 60.f;
	float num3 = eye_serverframes * Mathx::Max(Time::deltaTime(), Time::smoothDeltaTime(), Time::fixedDeltaTime());
	float num4 = ( last_tick_time + num2 + num3 ) * num;
	float num5 = LocalPlayer::Entity()->MaxVelocity() + LocalPlayer::Entity()->GetParentVelocity().magnitude();
	float num6 = LocalPlayer::Entity()->BoundsPadding() + num4 * num5;
	float num7 = LocalPlayer::Entity()->eyes()->position().distance(eyePos) + 0.01;
	if (num7 > num6)
	{
		hit = false; //eye_distance
	}
	float num8 = Mathf::Abs(LocalPlayer::Entity()->GetMountVelocity().y + LocalPlayer::Entity()->GetParentVelocity().y);
	float num9 = LocalPlayer::Entity()->BoundsPadding() + num4 * num8 + LocalPlayer::Entity()->GetJumpHeight();
	float num10 = Mathf::Abs(LocalPlayer::Entity()->eyes()->position().y - eyePos.y) + 0.01;
	if (num10 > num9)
	{
		hit = false; //eye_altitude
	}
	return hit;
}