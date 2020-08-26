# ConfigurableStart

This is the Source for the Mod ConfigurableStart

Include this in your Project if you want to make a Mod dependend on this Mod.

Adding Nodes to the Game can be done by Creating a Mod with a InitMenu that implements the ResourceNodeSetup Interface

![Image of SMLInitMenu](https://raw.githubusercontent.com/Nogg-aholic/ConfigurableStart/master/Images/InitMenu.png)

A Function will appear, create a Variable for each Output.

![Image of Interface](https://raw.githubusercontent.com/Nogg-aholic/ConfigurableStart/master/Images/Interface.png)

With the Default Values of those Variables , you can add Values for ConfigurableStart to Load.

![Image of DefaultValues](https://raw.githubusercontent.com/Nogg-aholic/ConfigurableStart/master/Images/DefaultValues.png)

New Nodetypes can be Created by using this Class : 

![Image of ModResourceNode1](https://raw.githubusercontent.com/Nogg-aholic/ConfigurableStart/master/Images/ModResourceNode1.png)

This Resource Node works similiar to the CSS Node, it needs a Mesh or Decal and Collision.

![Image of ModResourceNode2](https://raw.githubusercontent.com/Nogg-aholic/ConfigurableStart/master/Images/ModResourceNode2.png)

For this to Compile without Errors, you may have to make ModInitializerActorList in Source\SML\mod\ModHandler.h public.
