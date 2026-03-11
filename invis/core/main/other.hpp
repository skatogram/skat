struct Point {
	double x;
	double y;
};
Point rotatePointxx(const Point& point, const Point& center, double angle) {
	const double radians = angle * PI / 180.0;
	const double cosAngle = cos(radians);
	const double sinAngle = sin(radians);

	const double translatedX = point.x - center.x;
	const double translatedY = point.y - center.y;

	const double rotatedX = translatedX * cosAngle - translatedY * sinAngle;
	const double rotatedY = translatedX * sinAngle + translatedY * cosAngle;

	return { rotatedX + center.x, rotatedY + center.y };
}
ImVec2 rotatePoint1(const ImVec2& point, const ImVec2& center, float angle)
{
	float s = sin(angle);
	float c = cos(angle);

	ImVec2 rotatedPoint;
	rotatedPoint.x = (point.x - center.x) * c - (point.y - center.y) * s + center.x;
	rotatedPoint.y = (point.x - center.x) * s + (point.y - center.y) * c + center.y;

	return rotatedPoint;
}

void CalculateValidHitS_pos(Vector3 eye)
{
	if (target_ply != nullptr && funcs::weapon::bulletteleport && funcs::weapon::hitscan) {
		float radius_x = bigBulletSize;
		float radius_y = bigBulletSize - 0.2;
		Vector3 center = target_ply->BonePosition(AimSpotInt) - Vector3(0,0.1,0);
		const int numSegments = 5;
		static float rotation = 0.00f;
		rotation += 0.03f;
		const float angleIncrement = ((2 * IM_PI) / numSegments);
		int pointCount = 0;
		for (int i = 0; i < numSegments; ++i)
		{
			const float angle = angleIncrement * i + rotation;
			const float cosVal = std::cos(angle);
			const float sinVal = std::sin(angle);

			if (pointCount > 0) break;
			float x = center.x + radius_x * cosVal;
			float y = center.y + radius_y * sinVal;
			float z = center.z + radius_x * sinVal;
			float y2 = center.y + radius_y * cosVal;
			/*DDraw::Sphere(Vector3(x, y, center.z), 0.05f, Color(1, 1, 1, 1), 0.01f, false, false);
			DDraw::Sphere(Vector3(x, center.y, z), 0.05f, Color(1, 1, 1, 1), 0.01f, false, false);
			DDraw::Sphere(Vector3(center.x, y2, z), 0.05f, Color(1, 1, 1, 1), 0.01f, false, false);*/
			if (LineOfSight(Vector3(x, y, center.z), center) && LineOfSight(Vector3(x, y, center.z), eye))
			{
				funcs::other::BulletPos = Vector3(x, y, center.z);
				pointCount++;
			}
			if (LineOfSight(Vector3(x, center.y, z), center) && LineOfSight(Vector3(x, center.y, z), eye))
			{
				funcs::other::BulletPos = Vector3(x, center.y, z);
				pointCount++;
			}
			if (LineOfSight(Vector3(center.x, y2, z), center) && LineOfSight(Vector3(center.x, y2, z), eye))
			{
				funcs::other::BulletPos = Vector3(center.x, y2, z);
				pointCount++;
			}
			if (funcs::other::BulletPos.distance(center) > radius_x)
			{
				funcs::other::BulletPos = Vector3::Zero();
			}
		}
	}
}

static bool TestNoClipping(Vector3 oldPos, Vector3 newPos, float radius, float backtracking, bool sphereCast, bool vehicleLayer = false)
{
	int num = 429990145;
	if (!vehicleLayer)
	{
		num &= -8193;
	}
	Vector3 normalized = (newPos - oldPos).normalized();
	Vector3 vector = oldPos - normalized * backtracking;
	float magnitude = (newPos - vector).magnitude();
	Ray ray = Ray(vector, normalized);
	RaycastHit hitInfo;

	bool flag = Physics::Raycast(ray, magnitude + radius, num);
	if (!flag && sphereCast)
	{
		flag = Physics::SphereCast(ray, radius, magnitude, num);
	}
	return flag/* && GamePhysics::Verify(hitInfo, 0.f)*/;
}

static float NoClipRadius(float margin)
{
	return 0.5f - margin;
}

bool ValidateEyePos(Vector3 eyePos)
{
	auto player = LocalPlayer::Entity();
	bool flag = true;
	if (eyePos == Vector3::Zero())
	{
		flag = false;
	}
	static float eye_losradius = 0.18f;
	static float eye_noclip_cutoff = 0.06f;
	static float eye_noclip_margin = 0.21f;
	static float eye_noclip_backtracking = 0.01f;
	static int noclip_protection = 3;

	int num11 = 2162688 | 8388608 | 134217728;
	Vector3 center = player->eyes()->center();
	Vector3 position = player->eyes()->position();
	if (!LineOfSightRadius(center, position, num11, eye_losradius) || !LineOfSightRadius(position, eyePos, num11, eye_losradius))
	{
		flag = false;
	}
	Vector3 position2 = player->eyes()->position();
	float num15 = position2.distance(eyePos);
	if (num15 > eye_noclip_cutoff)
	{
		if (TestNoClipping(position2, eyePos, NoClipRadius(eye_noclip_margin), eye_noclip_backtracking, noclip_protection >= 2, false))
		{
			flag = false;
		}
	}
	else if (num15 > 0.01f && TestNoClipping(position2, eyePos, 0.01f, eye_noclip_backtracking, noclip_protection >= 2, false))
	{
		flag = false;
	}

	return flag;
}

void validatemanipulatorpos(float maxxzmanipulator, float maxymanipulator)
{
	Vector3 targetheadpos =  funcs::other::BulletPos != Vector3::Zero() ? funcs::other::BulletPos : target_ply->BonePosition(AimSpotInt);
	float ymanipulator = maxymanipulator - 0.25 + (maxxzmanipulator / 40);
	float xzmanipulator = maxxzmanipulator - 0.20 + (maxxzmanipulator / 50);
	Vector3 localheadpos = LocalPlayer::Entity()->transform()->position() + LocalPlayer::Entity()->transform()->up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);
	Vector3 choice = Vector3::Zero();

	float radius = xzmanipulator;
	float angleStep = 2 * IM_PI;
	static float rotation = 0.00f;
	rotation += 0.3f;
	float angle = angleStep + rotation;

	ImVec2 rotateup = rotatePoint1(ImVec2(radius, 0), ImVec2(0, 0), angle);
	ImVec2 rotatedown = rotatePoint1(ImVec2( - radius, 0), ImVec2(0, 0), angle);

	std::array<Vector3, 8> arr = {
		Vector3(rotateup.x, ymanipulator, rotateup.y),
		Vector3(-rotateup.x, ymanipulator, rotateup.y),
		Vector3(rotateup.x, ymanipulator, -rotateup.y),
		Vector3(-rotateup.x, ymanipulator, -rotateup.y),
		Vector3(rotatedown.x, 0.2, rotatedown.y),
		Vector3(-rotatedown.x, 0.2, rotatedown.y),
		Vector3(rotatedown.x, 0.2, -rotatedown.y),
		Vector3(-rotatedown.x, 0.2, -rotatedown.y)
	};
	for (auto s : arr) {
		Vector3 point = localheadpos + s;
		//DDraw::Sphere(point, 0.1f, Color(1, 1, 1, 1), 0.01f, false, false);
		CalculateValidHitS_pos(point);
		if (!ValidateEyePos(point) || !LineOfSight(point, targetheadpos) || !check_eye(point)) continue;
		funcs::manipulator::m_manipulate = point;
		choice = s;
		break;
	}
	if (choice.empty()) {
		funcs::manipulator::m_manipulate = Vector3::Zero();
		return;
	}
	funcs::manipulator::m_manipulate = choice;
}

void DrawCircle(Vector3 center, float radius, bool visible)
{
	Color color = Color(77, 0, 0, 77);
	const int numSegments = 20;
	const float angleIncrement = 2.0f * static_cast<float>(M_PI) / static_cast<float>(numSegments);

	if (visible)
		color = Color(0, 77, 0, 77);
	else
		color = Color(77, 0, 0, 77);

	for (int i = 0; i < numSegments; ++i)
	{
		float angle = angleIncrement * static_cast<float>(i);
		float x = center.x + radius * std::cos(angle);
		float z = center.z + radius * std::sin(angle);

		angle += angleIncrement;
		float x1 = center.x + radius * std::cos(angle);
		float z1 = center.z + radius * std::sin(angle);

		DDraw::Line(Vector3(x, center.y, z), Vector3(x1, center.y, z1), color, 0.01f, false, true);
	}
}

namespace other {
	void find_manipulate_angle() {
		auto player = LocalPlayer::Entity();
		if (target_ply == nullptr) return;

		float timeSinceLastTick = (Time::realtimeSinceStartup() - player->lastSentTickTime());
		float last_tick_time = Mathf::Max(0.f, Mathf::Min(timeSinceLastTick, 1.f));
		float num = 1.5f;
		float eye_clientframes = 2.0f;
		float eye_serverframes = 2.0f;
		float num2 = eye_clientframes / 60.f;
		float num3 = eye_serverframes * Mathx::Max(Time::deltaTime(), Time::smoothDeltaTime(), Time::fixedDeltaTime());
		float num4 = (last_tick_time + num2 + num3) * num;
		/*float num5 = 5.5 + player->GetParentVelocity().Magnitude() + player->GetMountVelocity().Magnitude();*/
		float num5 = player->MaxVelocity() + player->GetParentVelocity().Magnitude();
		float num6 = player->BoundsPadding() + num4 * num5; // бок десинка

		float num8 = Mathf::Abs(player->GetMountVelocity().y + player->GetParentVelocity().y);
		float num9 = player->BoundsPadding() + num4 * num8 + player->GetJumpHeight(); //верх десинка

		bool visible = false;

		Vector3 targetPos = funcs::other::BulletPos != Vector3::Zero() ? funcs::other::BulletPos : target_ply->BonePosition(AimSpotInt);

		if (LineOfSight(targetPos, player->eyes()->position())) {
			visible = true;
		}
		DrawCircle(player->BonePosition(penis), num6, visible);
		validatemanipulatorpos( num6, num9 - 0.1 );
		
		
	}
}