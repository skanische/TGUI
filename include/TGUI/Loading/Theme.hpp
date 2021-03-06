/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_THEME_HPP
#define TGUI_THEME_HPP

#include <TGUI/Loading/ThemeLoader.hpp>
#include <TGUI/Renderers/WidgetRenderer.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief This class can be used to manage the widget renderers
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API Theme
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Constructs the theme class, with an optional theme file to load
        ///
        /// @param primary  Primary parameter for the theme loader (filename of the theme file in DefaultThemeLoader)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Theme(const std::string& primary = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Destructor
        ///
        /// When a pointer to this theme was passed to setDefault, the default theme will be reset.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~Theme();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the primary theme loader parameter
        ///
        /// @param primary  Primary parameter for the theme loader (filename of the theme file in DefaultThemeLoader)
        ///
        /// When the theme was loaded before and a renderer with the same name is encountered, the widgets that were using
        /// the old renderer will be reloaded with the new renderer.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::string& primary);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets data for the renderers
        ///
        /// @param id  The secondary parameter for the theme loader (name of section in theme file in DefaultThemeLoader).
        ///
        /// @return Shared renderer data
        ///
        /// @throw Exception if theme loader fails to load the requested renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<RendererData> getRenderer(const std::string& id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets data for the renderers
        ///
        /// @param id  The secondary parameter for the theme loader (name of section in theme file in DefaultThemeLoader).
        ///
        /// @return Shared renderer data
        ///
        /// Unlike getRenderer which throws an exception, this function will return nullptr when the renderer is not found
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::shared_ptr<RendererData> getRendererNoThrow(const std::string& id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Manually adds a renderer data to the theme
        ///
        /// @param id       Identifier of the renderer
        /// @param renderer The renderer to add
        ///
        /// If a renderer with the same id already exists then it will be replaced by this one.
        /// Widgets using the old renderer will keep using that old renderer and remain unchanged.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void addRenderer(const std::string& id, std::shared_ptr<RendererData> renderer);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Manually removes a renderer to the theme
        ///
        /// @param id  Identifier of the renderer
        ///
        /// @return True when removed, false when the identifier did not match any renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeRenderer(const std::string& id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the primary theme loader parameter
        /// @return Primary parameter for the theme loader (filename of the theme file in DefaultThemeLoader)
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::string& getPrimary() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the function that will load the widget theme data
        ///
        /// @param themeLoader  Pointer to the new loader
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static void setThemeLoader(std::shared_ptr<BaseThemeLoader> themeLoader);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the function that is currently being used to load the widget theme data
        ///
        /// @return  Theme loader
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static std::shared_ptr<BaseThemeLoader> getThemeLoader();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the theme class that widgets use by default
        ///
        /// @param theme  Theme to use as default
        ///
        /// The default theme will automatically be reset to nullptr when the theme that is pointed to is destructed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static void setDefault(Theme* theme);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a pointer to the theme class that widgets use by default
        ///
        /// @return Default theme
        ///
        /// @warning When setDefault was not called or was given a nullptr as parameter, getDefault will return the default
        ///          theme. If you set textures in this theme then you MUST call setDefault(nullptr) before the end of the
        ///          program to prevent a potential crash due to undefined order of destruction.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static Theme* getDefault();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        static Theme* m_defaultTheme;
        static std::shared_ptr<BaseThemeLoader> m_themeLoader;  ///< Theme loader which will do the actual loading
        std::map<std::string, std::shared_ptr<RendererData>> m_renderers; ///< Maps ids to renderer datas
        std::string m_primary;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_THEME_HPP
