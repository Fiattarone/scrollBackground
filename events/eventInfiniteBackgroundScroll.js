export const id = "EVENT_INFINITE_BACKGROUND_SCROLL";
export const name = "Infinite Background Scroll";
export const groups = ["Background Effects"];
export const fields = [
  {
    key: "direction",
    label: "Direction",
    type: "select",
    options: [
      ["Horizontal", "horizontal"],
      ["Vertical", "vertical"],
    ],
    defaultValue: "horizontal",
  },
  {
    key: "speed",
    label: "Scroll Speed",
    type: "number",
    defaultValue: 1,
    min: 1,
    max: 100,
  },
  {
    key: "reverse",
    label: "Reverse",
    type: "checkbox",
    defaultValue: false,
  },
];

export const compile = (input, helpers) => {
  const { _stackPushConst, _callNative, _stackPop } = helpers;

  // Push parameters in the order: speed, direction, reverse.
  _stackPushConst(input.speed || 1); // Bottom of stack: speed
  _stackPushConst(input.direction === "horizontal" ? 0 : 1); // Next: direction
  _stackPushConst(input.reverse ? 1 : 0); // Top of stack: reverse flag

  // Call the native function.
  _callNative("script_cmd_infinite_background_scroll");

  // Pop the 3 parameters off the stack.
  _stackPop(3);
};
