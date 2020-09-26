pEngine = Interfaces:GetEngine()
pEntityList = Interfaces:GetEntityList()

function OnCreateMove(cmd)
	local localPlayer = pEntityList:GetEntityFromIndex(pEngine:GetLocalPlayer())
	
	local flags = localPlayer:GetFlasg()
	if ((cmd.Buttons & 2) > 0 ) and (not(flags & 1 > 0)) then
		cmd.Buttons = (cmd.Buttons & -3)
	end
end

Hooks:Register(HOOK_CREATEMOVE, OnCreateMove)
