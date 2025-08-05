# tap-hold-button

An Arduino sketch to support both **momentary** and **latch (hold)** modes with a single footswitch.

## Features

- **Momentary mode** (press and hold)
- **Latch mode** (tap to toggle)
- **Double-tap to exit latch mode**
- Ignores unintended release events after double-tap
- Clean logic with [JC_Button](https://github.com/JChristensen/JC_Button) library

## Behavior

- Short press: enter **Latch mode**
- Long press: enter **Momentary mode**
- Double tap (in latch mode): turn off and exit latch mode
- Release is skipped right after double tap to avoid accidental re-triggering
