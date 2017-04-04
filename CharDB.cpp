#include "stdafx.h"
#include "SA_UC.h"
#include "../../GA_Library/GA_Library/GA_Library.h"

// Initializes the ASG structs w/o assist listings
namespace ASGS
{
	extern characterInfo aSGIndex[15] = {
		{ 0, "None", "None", 0, { "--" }, { "--" }, { "--" }, { "--" }, { "--" } },
		{ 1, "Beowulf", "Beowulf", 0, {}, {}, {}, {}, {} },
		{ 2, "Big Band", "Saxploitation", 0,{},{},{},{},{} },
		{ 3, "Cerebella", "Cerebella", 0,{},{},{},{},{} },
		{ 4, "Double", "Politician Double", 0,{},{},{},{},{} },
		{ 5, "Eliza", "Eliza", 0,{},{},{},{},{} },
		{ 6, "Filia", "Filia", 0,{},{},{},{},{} },
		{ 7, "Fukua", "Fukua", 0,{},{},{},{},{} },
		{ 8, "Ms. Fortune", "Ms. Fortune", 0,{},{},{},{},{} },
		{ 9, "Painwheel", "Valley Girl Painwheel", 0,{},{},{},{},{} },
		{ 10, "Parasoul", "Salty Parasoul", 0,{},{},{},{},{} },
		{ 11, "Peacock", "Peacock", 0,{},{},{},{},{} },
		{ 12, "Robo Fortune", "Robo Fortune", 0,{},{},{},{},{} },
		{ 13, "Squigly", "Squigly", 0,{},{},{},{},{} },
		{ 14, "Valentine", "Valentine", 0,{},{},{},{},{} }
	};
}
// Initializes the assist listings for each ASG
void populateCharDB()
{
	// Beowulf
	ASGS::aSGIndex[1].normals = {
		"s.lp - Cheap Pop",
		"s.mp - Pipe Bomb",
		"s.hp - Hurting Hammer/Alpha Clinch",
		"s.lk - Low Town",
		"s.mk - Wulf Kick",
		"s.hk - Lone Boot",
		"c.lp - Wulf Paw",
		"c.mp - Potato",
		"c.hp - Nosebleed Seat/Grendel Flex",
		"c.lk - Trepak Attack",
		"c.mk - Ankle Lace",
		"c.hk - Geatish Leg Sweep/Gigan Arm Sweep" };
	ASGS::aSGIndex[1].specials = {
		"qcf.lp - Hurting Hurl (low)",
		"qcf.mp - Hurting Hurl (med)",
		"qcf.hp - Hurting Hurl (high)",
		"qcf.lk - Wulf Blitzer (low)",
		"qcf.mk - Wulf Blitzer (med)",
		"qcf.hp - Wulf Blitzer (high)",
		"qcf.throw - Wulf Shoot" };
	ASGS::aSGIndex[1].misc = {
		"Throw - Clinch Up",
		"Taunt - Aroo Ready? (lp, mp, f, lk, mk)",
		"Dash",
		"Backdash" };
	moveListPopulate(ASGS::aSGIndex[1]);

	// Big Band
	ASGS::aSGIndex[2].normals = {
		"s.lp - Honky Tonk",
		"s.mp - Free Form",
		"s.hp - Air Mail Special",
		"s.lk - Hot Socks",
		"s.mk - Pneumatic Slide",
		"s.hk - Kick Stand",
		"c.lp - Ring-a-Ding",
		"c.mp - Glissando",
		"c.hp - Overblow",
		"c.lk - Sharp Note",
		"c.mk - Bass Drop",
		"c.hk - Low Rank" };
	ASGS::aSGIndex[2].specials = {
		"[b]f.lp - Brass Knuckles (low)",
		"[b]f.mp - Brass Knuckles (med)",
		"[b]f.hp - Brass Knuckles (high)",
		"[b]f.lk - Take The A Train (low)",
		"[b]f.mk - Take The A Train (med)",
		"[b]f.hk - Take The A Train (high)",
		"qcb.lk - Giant Step (low)",
		"qcb.mk - Giant Step (med)",
		"qcb.hk - Giant Step (high)",
		"dp.lp - Beat Extend (low)",
		"dp.mp - Beat Extend (med)",
		"dp.hp - Beat Extend (high)" };
	ASGS::aSGIndex[2].misc = {
		"Throw - Heavy Toll",
		"Taunt - Bagpipe Blues (f, hp, mp, lp, f)",
		"Dash",
		"Backdash" };
	moveListPopulate(ASGS::aSGIndex[2]);

	// Cerebella
	ASGS::aSGIndex[3].normals = {
		"s.lp - Tune Up",
		"s.mp - Medici Shakedown",
		"s.hp - Tent Stake Hammer",
		"s.lk - Point Cut",
		"s.mk - Cugine Kick",
		"s.hk - Adagio Swing",
		"c.lp - Kneecapper",
		"c.mp - Enforcer Elbow",
		"c.hp - Boost-iere",
		"c.lk - Diamond Scratch",
		"c.mk - Loop de Loop",
		"c.hk - Medici Legbreaker",
		"f.HP - Titan Knuckle" };
	ASGS::aSGIndex[3].specials = {
		"[b]f.k - Tumbling Run",
		"[b]f.lp+lk - Run Stop",
		"[b]f.mp+mk - Kanchou",
		"[b]f.hp+hk -Battle Butt",
		"qcf.lp - Lock'n'Load (low)",
		"qcf.mp - Lock'n'Load (med)",
		"qcf.hp - Lock'n'Load (high)",
		"dp.lp - Diamond Deflector",
		"dp.mp - Devil Horns",
		"dp.hp - Cere-copter",
		"qcf.throw - Diamond Drop",
		"qcb.throw - Merry Go-Rilla",
		"dp.throw - Excellebella" };
	ASGS::aSGIndex[3].misc = {
		"Throw - Cere-rana",
		"Taunt - Medici Muscle (lp, mp, b, lp, mk)",
		"Dash",
		"Backdash" };
	moveListPopulate(ASGS::aSGIndex[3]);

	// Double
	ASGS::aSGIndex[4].normals = {
		"s.lp - Standing Jab",
		"s.mp - Strong Pie",
		"s.hp - Fugazi Knuckle",
		"s.lk - Substitute Short",
		"s.mk - Too Forward",
		"s.hk - Impawster",
		"c.lp - Crouching Jab",
		"c.mp - Elbow Emulator",
		"c.hp - Double Drawn Weave",
		"c.lk - Stamp",
		"c.mk - Cliché",
		"c.hk - Sweeping Generalization" };
	ASGS::aSGIndex[4].specials = {
		"b.lk+hk - Cilia Slide",
		"qcf.lp - Luger Replica (low)",
		"qcf.mp - Luger Replica (med)",
		"qcf.hp - Luger Replica (high)",
		"dp.lk - Hornet Bomber (low)",
		"dp.mk - Hornet Bomber (med)",
		"dp.hk - Hornet Bomber (high)" };
	ASGS::aSGIndex[4].misc = {
		"Throw - Godhand",
		"Taunt - False Intentions (lp, lk, mk, hk, hp, mp)",
		"qcb.k - Flesh Step",
		"Dash",
		"Backdash" };
	moveListPopulate(ASGS::aSGIndex[4]);

	// Eliza
	ASGS::aSGIndex[5].normals = {
		"s.lp - Wadjab",
		"s.mp - Siren Serpopards",
		"s.hp - Sirocco Storm",
		"s.lk - Sandal Wedge",
		"s.mk - Chaos Banish",
		"s.hk - Solar Arc",
		"c.lp - Nemes Set",
		"c.mp - Middle of the Sphynx",
		"c.hp - Isis Wings",
		"c.lk - Bast's Cuff",
		"c.mk - Sobek Slide",
		"c.hk - Solar Barge" };
	ASGS::aSGIndex[5].specials = {
		"qcb.lp - Warrior's Khopesh",
		"qcb.mp - Butcher's Blade",
		"qcb.hp - Carpenter's Axe",
		"qcf.lk - Throne of Isis",
		"qcf.mk - Dive of Horus",
		"qcf.hk - Weight of Anubis",
		"qcb.lk - Osiris Spiral (low)",
		"qcb.mk - Osiris Spiral (med)",
		"qcb.hk - Osiris Spiral (high)",
		"dp.lp - Upper Khat (low)",
		"dp.mp - Upper Khat (med)",
		"dp.hp - Upper Khat (high)" };
	ASGS::aSGIndex[5].misc = {
		"Throw - Lower Domain",
		"Taunt - Scarlet Ladies (mk, lp, d, lp, mp)",
		"Dash",
		"Backdash" };
	moveListPopulate(ASGS::aSGIndex[5]);

	// Filia
	ASGS::aSGIndex[6].normals = {
		"s.lp - Snip Snip",
		"s.mp - Thinning Shears",
		"s.hp - Chompadour",
		"s.lk - Knee High",
		"s.mk - Leg Warmer",
		"s.hk - Samson Boot",
		"c.lp - Comb Under",
		"c.mp - Ariel Rave",
		"c.hp - Queue Sting",
		"c.lk - Ankle Sock",
		"c.mk - French Twist",
		"c.hk - Tread Of Hair" };
	ASGS::aSGIndex[6].specials = {
		"qcf.lp - Ringlet Spike (low)",
		"qcf.mp - Ringlet Spike (med)",
		"qcf.hp - Ringlet Spike (high)",
		"qcb.lk - Hairball (low)",
		"qcb.mk - Hairball (med)",
		"qcb.hk - Hairball (high)",
		"dp.lp - Updo (low)",
		"dp.mp - Updo (med)",
		"dp.hp - Updo (high)" };
	ASGS::aSGIndex[6].misc = {
		"Throw - Samson Cuddle",
		"Taunt - Born With It (lp, mp, f, mk, mk)",
		"qcf.lk - Ringlet Psych (low)",
		"qcf.mk - Ringlet Psych (med)",
		"qcf.hk - Ringlet Psych (high)",
		"Dash",
		"Backdash" };
	moveListPopulate(ASGS::aSGIndex[6]);

	// Fukua
	ASGS::aSGIndex[7].normals = {
		"s.lp - Standing Jab",
		"s.mp - Thinning Shears",
		"s.hp - Chompadour",
		"s.lk - Knee High",
		"s.mk - Fukua sets mode +k",
		"s.hk - Shamone Boot",
		"c.lp - Crouching Jab",
		"c.mp - Ariel Rave",
		"c.hp - Queue Sting",
		"c.lk - Ankle Sock",
		"c.mk - French Twist",
		"c.hk - Tread Of Hair" };
	ASGS::aSGIndex[7].specials = {
		"qcf.lp - Love Dart (low)",
		"qcf.mp - Love Dart (med)",
		"qcf.hp - Love Dart (high)",
		"qcf.lk - Platonic Drillationship (low)",
		"qcf.mk - Platonic Drillationship (med)",
		"qcf.hk - Platonic Drillationship (high)",
		"qcb.lk - Forever A Clone (low)",
		"qcb.mk - Forever A Clone (med)",
		"qcb.hk - Forever A Clone (high)",
		"qcf.throw - Tender Embrace",
		"qcb.throw - Inevitable Snuggle" };
	ASGS::aSGIndex[7].misc = {
		"Throw - Shamone Cuddle",
		"Taunt - Breakdown (lk, mk, b, mp, mp)",
		"Dash",
		"Backdash" };
	moveListPopulate(ASGS::aSGIndex[7]);

	// Ms. Fortune
	ASGS::aSGIndex[8].normals = {
		"s.lp - Neko Pun-ch",
		"s.mp - Facepalm",
		"s.hp - Ears Pierced",
		"s.lk - Fishbone Flop",
		"s.mk - One Two Punisher",
		"s.hk - Wheel Of Fortune",
		"c.lp - Toy Touch",
		"c.mp - Hand In Hand",
		"c.hp - High Brow",
		"c.lk - Knees And Toes",
		"c.mk - Nail Clipper",
		"c.hk - Kitten Spin" };
	ASGS::aSGIndex[8].specials = {
		"qcf.lp - Cat Scratch (low)",
		"qcf.mp - Cat Scratch (med)",
		"qcf.hp - Cat Scratch (high)",
		"qcb.p - Be Headed",
		"qcf.k - Cat Slide",
		"qcb.k - El Gato",
		"dp.lk - Fiber Upper (low)",
		"dp.mk - Fiber Upper (med)",
		"dp.hk - Fiber Upper (high)" };
	ASGS::aSGIndex[8].misc = {
		"Throw - Apotemnophobia",
		"Taunt - Nyaaawn (hp, lp, f, lp, lp)",
		"Dash",
		"Backdash" };
	moveListPopulate(ASGS::aSGIndex[8]);

	// Painwheel
	ASGS::aSGIndex[9].normals = {
		"s.lp - Enmity Nail",
		"s.mp - Revulsion Shank",
		"s.hp - Fury Sledge",
		"s.lk - Puncture",
		"s.mk - Warp Spasm",
		"s.hk - Fracture",
		"c.lp - Lacerate",
		"c.mp - Cruel Lily",
		"c.hp - Animosity Barbs",
		"c.lk - Pierce",
		"c.mk - Disfigure",
		"c.hk - Malice Clover",
		"f.hk - Ratchet Poppy" };
	ASGS::aSGIndex[9].specials = {
		"qcf.lp - Gae Bolga Stinger (low)",
		"qcf.mp - Gae Bolga Stinger (med)",
		"qcf.hp - Gae Bolga Stinger (high)",
		"qcf.lk - Buer Reaper (low)",
		"qcf.mk - Buer Reaper (med)",
		"qcf.hk - Buer Reaper (high)" };
	ASGS::aSGIndex[9].misc = {
		"Throw - Vice Crush",
		"Taunt - SMILE (mk, hk, d, mp, hp)",
		"qcb.k - Flight",
		"Dash",
		"Backdash" };
	ASGS::aSGIndex[9].assistOnly = {
		"dd.lk - Pinion Dash (low)",
		"dd.mk - Pinion Dash (med)",
		"dd.hk - Pinion Dash (high)", };
	moveListPopulate(ASGS::aSGIndex[9]);

	// Parasoul
	ASGS::aSGIndex[10].normals = {
		"s.lp - Touché",
		"s.mp - Coup d'arrêt",
		"s.hp - Arc de Feu",
		"s.lk - Persistence",
		"s.mk - Queen's Gambit",
		"s.hk - Elegance",
		"c.lp - Garde",
		"c.mp - Coup Double",
		"c.hp - Prominence",
		"c.lk - Virtue",
		"c.mk - Beauty",
		"c.hk - Honesty",
		"f.lp - Pistol Whip",
		"f.mp - Coulé",
		"f.hp - Lunge",
		"b.hk - Forbearance" };
	ASGS::aSGIndex[10].specials = {
		"[b]f.lp - Napalm Shot (low)",
		"[b]f.mp - Napalm Shot (med)",
		"[b]f.hp - Napalm Shot (high)",
		"[b]f.lk - Egret Call",
		"[b]f.mk - Egret Dive",
		"[b]f.hk - Egret Charge",
		"[d]u.lk - Napalm Trigger",
		"[d]u.mk - Napalm Quake",
		"[d]u.hk - Napalm Pillar",
		"qcb.lk - Napalm Toss (low)",
		"qcb.mk - Napalm Toss (med)",
		"qcb.hk - Napalm Toss (high)" };
	ASGS::aSGIndex[10].misc = {
		"Throw - Napalm Trap",
		"Taunt - Bâillement (lp, hp, b, lk, hk)",
		"Dash",
		"Backdash" };
	moveListPopulate(ASGS::aSGIndex[10]);

	// Peacock
	ASGS::aSGIndex[11].normals = {
		"s.lp - Poke!",
		"s.mp - Pie Splat",
		"s.hp - Screwball Cannonball",
		"s.lk - Pop Eye",
		"s.mk - Springboard Panic",
		"s.hk - Kick The Football, Peacock",
		"c.lp - Stuff n' Puff",
		"c.mp - Eyes Of Tomorrow",
		"c.hp - Red Hot Buckshot",
		"c.lk - Curb Your Shoe",
		"c.mk - Ant Wasted",
		"c.hk - Banjo Trouble" };
	ASGS::aSGIndex[11].specials = {
		"qcf.lp - Bang! (low)",
		"qcf.mp - Bang! (med)",
		"qcf.hp - Bang! (high)",
		"qcb.lp Shadow Of Impending Doom (low) (short)",
		"qcb.mp Shadow Of Impending Doom (med) (short)",
		"qcb.hp Shadow Of Impending Doom (high) (short)",
		"qcf.lk - George's Day Out",
		"qcf.lk - Boxcar George",
		"qcf.lk - George At The Air Show",
		"qcb.p+k - Fire In The Hole" };
	ASGS::aSGIndex[11].misc = {
		"Throw - Burlap Beatdown",
		"Taunt - Hi Hi Birdie (lk, hk, mp, mp, u)",
		"qcb.lk - The Hole Idea (low)",
		"qcb.mk - The Hole Idea (med)",
		"qcb.hk - The Hole Idea (high)",
		"Dash",
		"Backdash" };
	ASGS::aSGIndex[11].assistOnly = {
		"qcb.lp+mp Shadow Of Impending Doom (low) (long)",
		"qcb.mp+hp Shadow Of Impending Doom (med) (long)",
		"qcb.lp+hp Shadow Of Impending Doom (high) (long)" };
	moveListPopulate(ASGS::aSGIndex[11]);

	// Robo Fortune
	ASGS::aSGIndex[12].normals = {
		"s.lp - Catcher Tongue",
		"s.mp - Flex Capacitor",
		"s.hp - Collimating Saw",
		"s.lk - HF Quartz Blade",
		"s.mk - Overclawk",
		"s.hk - Device Driver",
		"c.lp - Hearing Blade",
		"c.mp - Gain Medium",
		"c.hp - Grounding Pound",
		"c.lk - LF Quartz Blade",
		"c.mk Scroll Heel",
		"c.hk - Launch Headrone" };
	ASGS::aSGIndex[12].specials = {
		"qcf.lp - Theonite Beam (low)",
		"qcf.mp - Theonite Beam (med)",
		"qcf.hp - Theonite Beam (high)",
		"qcf.lk - Danger!  Head Swap Action!",
		"qcf.mk - Flailing Arm Hazard!",
		"qcf.hk - Rotating Component Hazard",
		"qcb.lk - Headrone RAM",
		"qcb.mk - Headrone Impact",
		"qcb.hk - Headrone Salvo" };
	ASGS::aSGIndex[12].misc = {
		"Throw - Blast Processor",
		"Taunt - \"Really Talks!\"  (hp, lk, b, lp, lp)",
		"Dash",
		"Backdash" };
	moveListPopulate(ASGS::aSGIndex[12]);

	// Squigly
	ASGS::aSGIndex[13].normals = {
		"s.lp - Lich Slap",
		"s.mp - Piercing Gaze",
		"s.hp - Bone Knuckle",
		"s.lk - Croisé",
		"s.mk - Death Drop",
		"s.hk - Dust To Dust",
		"c.lp - Tail Light",
		"c.mp - Serpent Spear",
		"c.hp - Cremation",
		"c.lk - Écart",
		"c.mk - En Pointe",
		"c.hk - Dance Of Salome",
		"f.hp - Ashes To Ashes" };
	ASGS::aSGIndex[13].specials = {
		"qcf.lp - One Inch Punch",
		"qcf.mp - Center Stage",
		"qcf.hp - Drag'n'Bite",
		"qcf.lp - Arpeggio",
		"qcf.mp - Silver Chord",
		"qcf.hp - Tremolo",
		"dp.p - Draugen Punch" };
	ASGS::aSGIndex[13].misc = {
		"Throw - Pass Away",
		"Taunt - Snake Charmer (lp, lp, f, lk, hp)",
		"Dash",
		"Backdash" };
	moveListPopulate(ASGS::aSGIndex[13]);

	// Valentine
	ASGS::aSGIndex[14].normals = {
		"s.lp - Check Up",
		"s.mp - Transfemoral Amputation",
		"s.hp - Thoracotomy",
		"s.lk - Shin Splinet",
		"s.mk - Chishibuki Juuji",
		"s.hk - IV Naginata",
		"c.lp - Knee-jerk Hammer",
		"c.mp - Venessection",
		"c.hp - Skyward Strike",
		"c.lk - Gedan Juuji",
		"c.mk - Kakushi Caliper",
		"c.hk - Kiri Barai" };
	ASGS::aSGIndex[14].specials = {
		"qcf.lp - Dead Cross (low)",
		"qcf.mp - Dead Cross (med)",
		"qcf.hp - Dead Cross (high)",
		"qcf.lk - Savage Bypass (low)",
		"qcf.mk - Savage Bypass (med)",
		"qcf.hk - Savage Bypass (high)",
		"qcb.lp - Vial Hazard (purple: poison)",
		"qcb.mp - Vial Hazard (green: hit-stop)",
		"qcb.lp - Vial Hazard (orange: input lag)",
		"qcb.throw - Mortuary Drop" };
	ASGS::aSGIndex[14].misc = {
		"Throw - Anasthesia",
		"Taunt - Chocoglycemia (lp, mk, b, mp, hk)",
		"Dash",
		"Backdash" };
	moveListPopulate(ASGS::aSGIndex[14]);
}
// Populates the move listings & move total values for each ASG
void moveListPopulate(characterInfo &selectedASG)
{
	selectedASG.moveList.push_back("None");
	for (unsigned int x = 0; x < selectedASG.normals.size(); x++)
		selectedASG.moveList.push_back(selectedASG.normals[x]);
	for (unsigned int x = 0; x < selectedASG.specials.size(); x++)
		selectedASG.moveList.push_back(selectedASG.specials[x]);
	for (unsigned int x = 0; x < selectedASG.misc.size(); x++)
		selectedASG.moveList.push_back(selectedASG.misc[x]);
	for (unsigned int x = 0; x < selectedASG.assistOnly.size(); x++)
		selectedASG.moveList.push_back(selectedASG.assistOnly[x]);
	selectedASG.moveTotal = selectedASG.moveList.size();
}


