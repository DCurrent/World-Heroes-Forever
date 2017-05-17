# World-Heroes-Timeless

World Heroes Timeless is a remake in progress of World Heroes Supreme Justice, an OpenBOR module originally crafted by magggas (Final Fight style beat em’ take on the World Heroes series of fighting games). I am also a fan of the World Heroes series and had planned to produce a module myself, but magggas beat me to the punch. :)

WH Supreme Justice is an excellent piece of craftsmanship and I recommend you try it out right now. Sign up at www.chronocrash.com and you can get it [here](http://www.chronocrash.com/forum/index.php?action=tpmod;dl=item107).

My finished version will for all intents and purposes be an entirely new game. I’m using Supreme Justice as a starting off point, but all assets will be new - even the ones that look similar are all being remastered to take advantage of OpenBOR’s palette swapping features, .png image format in place of .gif, transparences, and a larger playfield (472x272 vs. 320x240). Existing stages will be split into additional scrolling layers whenever possible.

Gameplay will have a different control scheme and feel. The Punch, Kick, Jump, and Block control scheme of Supreme Justice will be replaced with a simpler Attack, Jump, and Defense layout. Auto combos will now differ based on proximity and other in game factors. 

Most of the character design liberties taken by Supreme Justice will be removed. Instead, all effort will focus on bringing the characters' various unique abilities from the original series into the beat em’ up genre. For example, the generic Final Fight Style breakaway special shared by every fighter in Supreme Justice will be replaced with a character specific “ABC Special” from World Heroes Perfect (Hanzou’s attack cancel, Ryoko’s counter throws, etc.). In general, all character move sets will be expanded to reflect their original renditions. 

Below is the progress made prior to moving this project to Github. Further progress is documented via commits as normal:

## General

- Resolution upgraded from default (320*240) to widescreen (480*272).
- A lot of other things I forgot to write down before creating this document. :P

## HUD

- P1 MPbar setting configured for MP use.
- P1 HPbar setting configured for modified icon to accommodate MP use.

## USA Stage 1 (Construction Site)

- All .gif assets remastered as .png type.
- Scrolling layers increased to five (previously two).
- Added environmental palettes. Stage fades from mid-afternoon to sunset over time.
- Spawn coordinates adjusted to accommodate increased resolution.
- Bucket loader’s cab window is now real transparent glass.

## USA Stage 2 (Metal Mesh Deathmatch)

- All .gif assets remastered as .png type.
- Background appearance completely revamped with new two layer cityscape.
- Spawn coordinates adjusted to accommodate increased resolution.
- Water now displayed with “mode 7” effect.
- “Metal Mesh Deathmatch” sign is now a live multi-color rotating neon.
- Added environmental palettes. Stage fades from early evening to night over time.

## Characters

### Hanzou

- Icon divided for MP and HP use.

### Ray

- (In progress) All .gif assets remastered as .png type with smart palette.
- Animations enhanced (ex. Jab now has five unique sprites compared to two previously).
- Added BACKWALK animation.
- Added TURN animation.
- System of follow ups for main attack combo have been replaced with combostyle and atchain commands. Same effect but less complexity.
- Added close range combo finisher (Cross).
- Replace PAIN1 with multi frame animation.
- Replace PAIN2 (stun) with multi frame animation.
- Stays on screen after KO, with washed out tint.

