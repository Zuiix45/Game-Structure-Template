---@diagnostic disable: undefined-global, undefined-doc-name
-- This file is used to bind C++ functions to Lua. The functions in this file are called from Lua scripts.

-- The timer module is used to create and manage timers.

--- Creates timer and returns its identifier.
--- @return integer id of newly created timer.
createTimer = function ()
    return timerModule.createTimer()
end

--- Resets the specified timer.
--- @param timerID integer number The ID of the timer to reset.
resetTimer = function (timerID)
    timerModule.resetTimer(timerID)
end

--- Kills a timer with the specified timerID.
--- @param timerID integer The ID of the timer to be killed.
killTimer = function (timerID)
    timerModule.killTimer(timerID)
end

--- Returns the time difference for the specified timer ID.
--- @param timerID integer The ID of the timer.
--- @return number milliseconds The time difference for the timer.
getTimeDiff = function (timerID)
    return timerModule.getTimeDiff(timerID)
end

--- Sets a delay for the specified number of milliseconds.
--- @param milliseconds number The number of milliseconds to delay.
delay = function (milliseconds)
    timerModule.delay(milliseconds)
end

-- End of timer module functions.

-- The engine module is used to manage all objects

--- Creates an object with the specified layer and name.
--- @param layer integer The layer of the object.
--- @param name string The name of the object.
--- @return integer id of The created object.
createObject = function (layer, name)
    return engineModule.createObject(layer, name)
end

--- Deletes the object with the specified object ID.
--- @param objectId integer The ID of the object to delete.
deleteObject = function (objectId)
    engineModule.deleteObject(objectId)
end

--- Retrieves the object with the specified object ID.
--- @param objectId integer The ID of the object to retrieve.
obj = function (objectId)
    return engineModule.getObjectByID(objectId)
end

--- Retrieves the object with the specified name.
--- @param objectName string The name of the object to retrieve.
objn = function (objectName)
    return engineModule.getObjectByName(objectName)
end

--- Retrieves the ID of the object with the specified name.
--- @param name string The name of the object.
id = function (name)
    return engineModule.getObjectID(name)
end

--- Sets the layer of the object with the specified object ID.
--- @param objectId integer The ID of the object.
--- @param layer integer The new layer of the object.
setLayer = function (objectId, layer)
    engineModule.setLayer(objectId, layer)
end

--- Closes all animations of the object with the specified object ID.
--- @param objectId integer The ID of the object.
closeAnimations = function (objectId)
    engineModule.closeAnimations(objectId)
end

--- Changes the shaders of the object with the specified object ID.
--- @param objectId integer The ID of the object.
--- @param vertexShaderSource string The source code of the vertex shader.
--- @param fragmentShaderSource string The source code of the fragment shader.
changeShaders = function (objectId, vertexShaderSource, fragmentShaderSource)
    engineModule.changeShaders(objectId, vertexShaderSource, fragmentShaderSource)
end

--- Saves the sprite with the specified name to the specified path.
--- @param spriteName string The name of the sprite.
--- @param path string The path to save the sprite to.
--- @param flip boolean Whether to flip the sprite horizontally.
saveSprite = function (spriteName, path, flip)
    engineModule.saveSprite(spriteName, path, flip)
end

--- Retrieves the sprite with the specified name.
--- @param spriteName string The name of the sprite.
getSprite = function (spriteName)
    return engineModule.getSprite(spriteName)
end

--- Binds a script to the object with the specified object ID.
--- @param objectId integer The ID of the object.
--- @param scriptPath string The path to the script to bind.
bindScriptToObject = function (objectId, scriptPath)
    engineModule.bindScriptToObject(objectId, scriptPath)
end

-- End of engine module functions.

-- Functions for Animation class

createAnimation = function (sprites, fps, speed)
    local spritesList = SpriteList()
    for sprite in sprites do
        spritesList:addSprite(sprite)
    end

    return Animation(spritesList, fps, speed)
end

createStaticAnimation = function (sprite)
    local spriteList = SpriteList()
    spriteList:addSprite(sprite)

    return Animation(spriteList, 0, 1)
end

deactivateAnimation = function (animation)
    animation:deactivate()
end

-- End of Animation class functions.

-- Functions for the object class

-- Constants for corner positions
TOP_LEFT_CORNER = 0
TOP_RIGHT_CORNER = 1
BOTTOM_LEFT_CORNER = 2
BOTTOM_RIGHT_CORNER = 3
ALL_CORNERS = 4

--- Sets the animation of an object
--- @param objectId integer The ID of the object
--- @param animation Animation The name of the animation
--- @return Animation animation Old animation of the object
setAnimation = function (objectId, animation)
    local object = obj(objectId)
    return object:setAnimation(animation)
end

--- Gets the current animation of an object
--- @param objectId integer The ID of the object
--- @return Animation animation The current animation of the object.
getCurrentAnimation = function (objectId)
    local object = obj(objectId)
    return object:getAnimation()
end

--- Shows an object
--- @param objectId integer The ID of the object
showObject = function (objectId)
    local object = obj(objectId)
    object:show()
end

--- Hides an object
--- @param objectId integer The ID of the object
hideObject = function (objectId)
    local object = obj(objectId)
    object:hide()
end

--- Checks if an object is visible
--- @param objectId integer The ID of the object
--- @return boolean visiblity True if the object is visible, false otherwise
isVisible = function (objectId)
    local object = obj(objectId)
    return object:isVisible()
end

--- Gets the coordinates of an object
--- @param objectId integer The ID of the object
--- @return table coordinates A Table contains the X and Y coordinates of the object
getCoordinates = function(objectId)
    local object = obj(objectId)
    return {object:getX(), object:getY()}
end

--- Gets the width and height of an object
--- @param objectId integer The ID of the object
--- @return table bounds A Table contains the width and height of the object
getBounds = function(objectId)
    local object = obj(objectId)
    return {object:getWidth(), object:getHeight()}
end

--- Gets the rotation angle of an object
--- @param objectId integer The ID of the object
--- @return number angle The rotation angle of the object
getAngle = function(objectId)
    local object = obj(objectId)
    return object:getAngle()
end

--- Gets the color of an object
--- @param objectId integer The ID of the object
--- @param corner integer (optional) The corner position to get the color from (default: ALL_CORNERS)
--- @return table color The color of the object at the specified corner position
getColor = function(objectId, corner)
    corner = corner or ALL_CORNERS

    local object = obj(objectId)
    return object:getColor(corner)
end

--- Sets the X coordinate of an object
--- @param objectId integer The ID of the object
--- @param x number The new X coordinate
setX = function(objectId, x)
    local object = obj(objectId)
    object:setX(x)
end

--- Sets the Y coordinate of an object
--- @param objectId integer The ID of the object
--- @param y number The new Y coordinate
setY = function(objectId, y)
    local object = obj(objectId)
    object:setY(y)
end

--- Sets the width of an object
--- @param objectId integer The ID of the object
--- @param width number The new width
setWidth = function(objectId, width)
    local object = obj(objectId)
    object:setWidth(width)
end

--- Sets the height of an object
--- @param objectId integer The ID of the object
--- @param height number The new height
setHeight = function(objectId, height)
    local object = obj(objectId)
    object:setHeight(height)
end

--- Sets the rotation angle of an object
--- @param objectId integer The ID of the object
--- @param angle number The new rotation angle
setAngle = function(objectId, angle)
    local object = obj(objectId)
    object:setRotation(angle)
end

--- Sets the color of an object
--- @param objectId integer The ID of the object
--- @param r integer The red component of the color (0-255)
--- @param g integer The green component of the color (0-255)
--- @param b integer The blue component of the color (0-255)
--- @param a number (optional) The alpha component of the color (0-1) (default: 1.0)
--- @param corner integer (optional) The corner position to set the color for (default: ALL_CORNERS)
setColor = function(objectId, r, g, b, a, corner)
    a = a or 1.0
    corner = corner or ALL_CORNERS

    local object = obj(objectId)
    object:setColor(r, g, b, a, corner)
end
