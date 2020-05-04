#pragma once

/** @defgroup vector2 vector2
 * @{
 *
 * @brief Functions for 2-dimensional vector manipulations
 */

/**
 * @brief Struct that represents a vector in 2d space
 */
typedef struct vector2
{
    float x; /**< @brief The x component */
    float y; /**< @brief The y component */
} vector2;

/**
 * @return The sum of v1 and v2
 */
vector2 vector2_add(vector2 v1, vector2 v2);

/**
 * @return v1 subtracted by v2
 */
vector2 vector2_subtract(vector2 v1, vector2 v2);

/**
 * @return A vector2 in which every element of v is multiplied by k
 */
vector2 vector2_scalar_product(vector2 v, float k);

/**
 * @return The lenght of vector2 v
 */
float vector2_norm(vector2 v);

/**
 * @return The normalized version of vector2 v
 */
vector2 vector2_normalized(vector2 v);

/** @} end of vector2 */

