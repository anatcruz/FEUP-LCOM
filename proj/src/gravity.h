#pragma once

#include "vector2.h"

/** @defgroup gravity gravity
 * @{
 *
 * @brief Gravity-related functions
 */

/**
 * @brief Struct that contains the position and velocity of an object
 */
typedef struct gravity_object
{
    vector2 position; /**< @brief The position of an object */
    vector2 velocity; /**< @brief The velocity of an object */
} gravity_object;

/**
 * @brief Calculates the gravitational pull of a given body on gravity_object obj
 * 
 * @param body_pos The position of our body
 * @param body_grav_parameter The 
 * <a href="https://en.wikipedia.org/wiki/Standard_gravitational_parameter">gravitational parameter</a> 
 * of the body
 * @param obj A pointer to the object whose gravitational acceleration will be calculated
 * @return The gravitational acceleration vector of obj
 */
vector2 gravity_acc_vector(vector2 body_pos, float body_grav_parameter, const gravity_object *obj);

/**
 * @brief Updates the velocity and position of obj, using something similar to the 
 * <a href="https://en.wikipedia.org/wiki/Euler_method">Euler method</a> 
 * 
 * @param obj A pointer to the object whose state will be updated
 * @param acc The acceleration that obj is subjected to
 * @param delta The time delta in seconds
 */
void update_gravity_object(gravity_object *obj, vector2 acc, float delta);

/** @} end of gravity */

