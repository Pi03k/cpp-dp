#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

#define MOTIF

enum class IconType
{
	none,
	ok,
	cancel,
	warning,
	error
};

class Widget
{
	public:
		virtual void draw() = 0;
		virtual ~Widget() = default;
};

class Button : public Widget
{
	std::string caption_;
	IconType icon_type_;

	public:
	Button(const std::string& caption, IconType icon_type) : caption_{caption}, icon_type_{icon_type}
	{
	}

	std::string caption() const
	{
		return caption_;
	}

	IconType icon() const
	{
		return icon_type_;
	}
};

class Menu : public Widget
{
	std::string text_;

	public:
	Menu(const std::string& text) : text_{text}
	{
	}

	std::string text() const
	{
		return text_;
	}
};

class MotifButton : public Button
{
	public:
		using Button::Button;

		void draw() override
		{
			cout << "MotifButton [ " << caption() << " ]\n";
		}
};

class MotifMenu : public Menu
{
	public:
		using Menu::Menu;

		void draw() override
		{
			cout << "MotifMenu { " << text() << " }\n";
		}
};

class WindowsButton : public Button
{
	public:
		using Button::Button;

		void draw() override
		{
			cout << "WindowsButton [ " << caption() << " ]\n";
		}
};

class WindowsMenu : public Menu
{
	public:
		using Menu::Menu;

		void draw() override
		{
			cout << "WindowsMenu { " << text() << " }\n";
		}
};

class WidgetsFactory
{
	public:
		WidgetsFactory() = default;
		virtual ~WidgetsFactory() = default;
		virtual std::unique_ptr<Button> createButton(const std::string& caption, IconType) = 0;
		virtual std::unique_ptr<Menu> createMenu(const std::string& caption) = 0;
}; // class WidgetsFactory

class MotifWidgetsFactory : public WidgetsFactory
{
	public:
		std::unique_ptr<Button> createButton(const std::string& caption, IconType iconType) override
		{
			return std::make_unique<MotifButton>(caption, iconType);
		}

		std::unique_ptr<Menu> createMenu(const std::string& caption) override
		{
			return std::make_unique<MotifMenu>(caption);
		}
}; // class MotifWidgetFactory

class WindowsWidgetsFactory : public WidgetsFactory
{
	public:
		std::unique_ptr<Button> createButton(const std::string& caption, IconType iconType) override
		{
			return std::make_unique<WindowsButton>(caption, iconType);
		}
		std::unique_ptr<Menu> createMenu(const std::string& caption) override
		{
			return std::make_unique<WindowsMenu>(caption);
		}
}; // class WindowsWidgetFactory

class Window
{
	std::vector<std::unique_ptr<Widget>> widgets;

	public:
	void display() const
	{
		std::cout << "######################\n";
		for (const auto& w : widgets)
			w->draw();
		std::cout << "######################\n\n";
	}

	void add_widget(std::unique_ptr<Widget> widget)
	{
		widgets.push_back(move(widget));
	}


};

class WindowOne : public Window
{

	public:
		WindowOne(WidgetsFactory& widgetsFactory)
		{
			add_widget(widgetsFactory.createButton("OK", IconType::ok));
			add_widget(widgetsFactory.createMenu("File"));
		}
};

class WindowTwo : public Window
{

	public:
		WindowTwo(WidgetsFactory& widgetsFactory)
		{
			add_widget(widgetsFactory.createMenu("Edit"));
			add_widget(widgetsFactory.createButton("OK", IconType::ok));
			add_widget(widgetsFactory.createButton("Cancel", IconType::cancel));
		}
};

int main(void)
{
#ifdef MOTIF
	MotifWidgetsFactory widgetsFactory;
#else // WINDOWS
	WindowsWidgetsFactory widgetsFactory;
#endif
	WindowOne w1(widgetsFactory);
	w1.display();

	WindowTwo w2(widgetsFactory);
	w2.display();
}
