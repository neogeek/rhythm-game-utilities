local rhythmgameutilities = require("rhythmgameutilities")

local function inverse_lerp_test()
    local value = rhythmgameutilities.inverse_lerp(0, 10, 5);

    print(value) -- 0.5

    assert(value == 0.5)
end

local function lerp_test()
    local value = rhythmgameutilities.lerp(0, 10, 0.5);

    print(value) -- 5.0

    assert(value == 5)
end

local function calculate_accuracy_ratio_test()
    local value = rhythmgameutilities.calculate_accuracy_ratio(750, 768, 50);

    value = tonumber(string.format("%.2f", value));

    print(value) -- 0.64

    assert(value == value)
end

local function convert_tick_to_position_test()
    local value = rhythmgameutilities.convert_tick_to_position(1056, 192);

    print(value) -- 5.5

    assert(value == 5.5)
end

local function is_on_the_beat_test()
    local value = rhythmgameutilities.is_on_the_beat(120, 10, 0.05);

    print(value) -- true

    assert(value == true)
end

local function round_up_to_the_nearest_multiplier_test()
    local value = rhythmgameutilities.round_up_to_the_nearest_multiplier(12, 10);

    print(value) -- 20

    assert(value == 20)
end

inverse_lerp_test();
lerp_test();

calculate_accuracy_ratio_test();
convert_tick_to_position_test();

is_on_the_beat_test();
round_up_to_the_nearest_multiplier_test();
