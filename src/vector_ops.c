t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;

	// Debugging cross product
	printf("Cross Product:\n");
	printf("  A: (%f, %f, %f)\n", a.x, a.y, a.z);
	printf("  B: (%f, %f, %f)\n", b.x, b.y, b.z);
	printf("  Result: (%f, %f, %f)\n", result.x, result.y, result.z);

	return result;
}

t_vec3	vec_normalize(t_vec3 v)
{
	float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

	// Debugging normalization
	printf("Normalize Vector:\n");
	printf("  Input: (%f, %f, %f), Length: %f\n", v.x, v.y, v.z, length);

	if (length == 0.0f)
		return (t_vec3){0.0f, 0.0f, 0.0f};

	return (t_vec3){v.x / length, v.y / length, v.z / length};
}
