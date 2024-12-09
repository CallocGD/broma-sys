# Broma-sys

Used for Parsing C++ like language to extract variable signatures and other informaiton. 
For more documentation SEE: [Geode Documentation](https://github.com/geode-sdk/broma)

## FYI
- This code is still in it's prototype phase and I need to cleanup some binding generation errors like
```evaluation of constant value failed attempt to compute `1_usize - 24_usize`, which would overflow```

## Why I wrote this
- Reverse Engineering via automation.
- As a Means of providing code-safety along with safer alternatives for using this brand new AST. 
- Easier ways to check for errors.

However the main work is not done yet. I am planning to add a new function called `parse_file_safely`
so that servers and discord bots will be able to handle parsing broma files multiple times without crashing when an error is hit, same goes for
[PyBroma](https://github.com/CallocGD/PyBroma) You can see my progress on getting that passed [here](https://github.com/geode-sdk/Broma/pull/7)

## Where's the frontend?
If your looking for the frontend we will put it on the in offical (Geometry Dash Reverse Engineering)[https://github.com/GD-RE] repos soon as 
all the rust bindings here have been completely fixed. I want to thank the reverse engineering community for getting us as far as we have.
This would not be possible without your help.
