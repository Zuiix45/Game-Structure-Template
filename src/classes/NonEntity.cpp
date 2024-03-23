#include "NonEntity.h"

NonEntity::NonEntity() : Object(ObjectType::NON_ENTITY) {
    effectByCamera(true); // all non entities are affected by camera
}