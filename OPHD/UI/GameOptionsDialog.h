#pragma once

#include "Core/Window.h"
#include "Core/Button.h"


class GameOptionsDialog : public Window
{
public:
	using ClickCallback = NAS2D::Signal<>;

	GameOptionsDialog();
	~GameOptionsDialog() override;

	void update() override;

	ClickCallback& SaveGame() { return mCallbackSave; }
	ClickCallback& LoadGame() { return mCallbackLoad; }
	ClickCallback& returnToGame() { return mCallbackReturn; }
	ClickCallback& returnToMainMenu() { return mCallbackClose; }

private:
	void onLoad();
	void onSave();
	void onReturn();
	void onClose();

	void onEnableChange() override;

	Button btnSave;
	Button btnLoad;
	Button btnReturn;
	Button btnClose;

	ClickCallback mCallbackSave;
	ClickCallback mCallbackLoad;
	ClickCallback mCallbackReturn;
	ClickCallback mCallbackClose;
};
