local rhythmgameutilities = require("rhythmgameutilities")

local function lerp_test()
    local value = rhythmgameutilities.lerp(0, 10, 0.5);

    print(value) -- 5.0

    assert(value == 5)
end

local function inverse_lerp_test()
    local value = rhythmgameutilities.inverse_lerp(0, 10, 5);

    print(value) -- 0.5

    assert(value == 0.5)
end

lerp_test();
inverse_lerp_test();
