function OnKey(key)
	if key.Type == EVENT_KEYDOWN then
		if key.KeyCode == KEY_DELETE then
			print("hey :)")
		end
	end
end

Hooks:Register(HOOK_KEYBOARD, OnKey)