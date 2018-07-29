# arma-3-Mission_Validator

Scans ArmA 3 multiplayer mission directories and reports if some important properties are missing.

How it works: scans directories and if mission.sqm file is found we have a mission, then checks if description.ext is found and reports if not.

Reads mission.sqm for player numbers and checks if mission name is set.

Reads description.ext and checks for important multiplayer parameters, reports if any of them are missing.

This tool only validates by reporting, it wont edit or fix your missions.
