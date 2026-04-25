## Mimo

My Attempt to make a compiler smaller than BrainFuck. lol

# Syntax
v2 is basically like BrainFuck, except it uses a state variable to change the forward/backward movement and increment/decrement behaviour simultaneously.

```
^: Flip state
>: Move forward/backward based on ^
_: Increment/Decrement based on ^
,: stdin/character input
':': checkpoint
?: Jump to the corresponding ':' if buffer isn't '0'
.: stdout/print

Everything Else: ignored, unprocessed. Could be used as comments.
```

*Note: v1 was about bit manipulation in an 8-bit size character buffer. But because of limited size (8-bit), it can't be considered as "Turing complete/equivalent" so I moved to a long array buffer.*

# Example
```
_____:>_____^>_^?>^_.
^>______:>>___:^>^___>^_^?^>>_^?>___.
>______:>^______>_^?>^__.
```
refer to: `test.mimo`

Output:
```
# Hi
```
