# EquipmentSystem

### Tools
-   Unreal Engine 4.25
-   Rider ([https://www.jetbrains.com/lp/rider-unreal/](https://www.jetbrains.com/lp/rider-unreal/))

### Assets
-   [https://craftpix.net/](https://craftpix.net/)
	-   [https://craftpix.net/freebies/free-game-icons-of-fantasy-potions-pack-1/](https://craftpix.net/freebies/free-game-icons-of-fantasy-potions-pack-1/)
	-   [https://craftpix.net/freebies/free-game-icons-of-fantasy-daggers-pack-2/](https://craftpix.net/freebies/free-game-icons-of-fantasy-daggers-pack-2/)
	-   [https://craftpix.net/freebies/free-game-icons-of-fantasy-knight-armor-pack-11/](https://craftpix.net/freebies/free-game-icons-of-fantasy-knight-armor-pack-11/)
-   [https://www.kenney.nl/](https://www.kenney.nl/)

### Notes
-    Items are set up as Primary Data Assets  with a base data asset class for consumables and equipables.
-    Items can be created in editor as Data Assets (See under Items folder)
-   Test Dagger locked to Spineboy's hand, those will spawn from the actor linked in the item data asset (spawning not implemented yet).  This uses a base class with the Bone Follower as to not break animation.
-   All native classes prefixed with "Ces" for "Character Equipment System".  I have found it easier to use a prefix for custom classes to easily search on them and separate them from engine and plugin classes.
-   Separation of data (Data Assets), logic (native classes), and presentation (UMG Widgets)
-   Opted to not do any widget binding between the native UMG classes and the UMG Blueprints.  I feel like they are too tightly coupled when it's dependent on the widget name remaining the same and hiding the logic of what's populating that widget.
- Slots have the ability to toggle what type of items are allowed to be placed in those slots.
- Inventory bag is done, Quick Slots and Equipment will show a message allowing or rejecting that item.  However, the item will not be placed in that slot yet, that has not been implemented.

### ToDo
-   Drop on Hotbar slot
-   Drop on Equip slot
-   Stack size limitations
-   Weight limitations
-   Item Actor from data assets spawns on equip/use

### Final Thoughts
My workflow generally consists of flowing something out in blueprints and then refactoring out the heavier/architecture logic into native base classes.  Unless I know it will need native classes, then I just start there.  For interface logic, I create a rough layout of the interface, then split out the data layer into native classes and leave the visual logic in UMG blueprints.  I try to make everything as decoupled as possible so it's open to change without breaking everything else.
