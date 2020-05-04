#include "gravity.h"

vector2 gravity_acc_vector(vector2 body_pos, float body_grav_parameter, const gravity_object *obj) {
  if (body_grav_parameter == 0) {
    vector2 zero = {.x = 0, .y = 0};
    return zero;
  }

  vector2 grav_direction = vector2_subtract(body_pos, obj->position);
  float grav_scalar = body_grav_parameter / (grav_direction.x * grav_direction.x + grav_direction.y * grav_direction.y);

  return vector2_scalar_product(vector2_normalized(grav_direction), grav_scalar);
}


void update_gravity_object(gravity_object *obj, vector2 acc, float delta) {
  vector2 delta_v = vector2_scalar_product(acc, delta);
  obj->velocity = vector2_add(obj->velocity, delta_v);
  obj->position = vector2_add(obj->position, vector2_scalar_product(obj->velocity, delta));
}
