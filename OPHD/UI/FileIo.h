#pragma once

#include "Core/Window.h"
#include "Core/Button.h"
#include "Core/TextField.h"
#include "Core/ListBox.h"

#include <NAS2D/Signal/Signal.h>
#include <NAS2D/EventHandler.h>


class FileIo : public Window
{
public:
	enum FileOperation
	{
		FILE_LOAD,
		FILE_SAVE
	};

	using FileOperationCallback = NAS2D::Signal<const std::string&, FileOperation>;

	FileIo();
	~FileIo() override;

	void setMode(FileOperation fileOp);
	void scanDirectory(const std::string& directory);

	FileOperationCallback& fileOperation() { return mCallback; }

	void update() override;

protected:
	void onDoubleClick(NAS2D::EventHandler::MouseButton button, int x, int y);
	void onKeyDown(NAS2D::EventHandler::KeyCode key, NAS2D::EventHandler::KeyModifier mod, bool repeat);

private:
	void onClose();
	void onFileIo();
	void onFileDelete();

	void onFileSelect();
	void onFileNameChange(TextControl* control);

	FileOperationCallback mCallback;

	FileOperation mMode;

	Button btnClose;
	Button btnFileOp;
	Button btnFileDelete;

	TextField txtFileName;

	ListBox<> mListBox;
};
