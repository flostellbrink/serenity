/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Tobias Christiansen <tobyase@serenityos.org>
 * Copyright (c) 2021-2023, Sam Atkins <atkinssj@serenityos.org>
 * Copyright (c) 2022-2023, MacDue <macdue@dueutil.tech>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "IdentifierStyleValue.h"
#include <LibGfx/Palette.h>
#include <LibWeb/DOM/Document.h>
#include <LibWeb/Layout/Node.h>

namespace Web::CSS {

ErrorOr<String> IdentifierStyleValue::to_string() const
{
    return String::from_utf8(CSS::string_from_value_id(m_id));
}

bool IdentifierStyleValue::has_color() const
{
    switch (m_id) {
    case ValueID::Currentcolor:
    case ValueID::LibwebLink:
    case ValueID::LibwebPaletteActiveLink:
    case ValueID::LibwebPaletteActiveWindowBorder1:
    case ValueID::LibwebPaletteActiveWindowBorder2:
    case ValueID::LibwebPaletteActiveWindowTitle:
    case ValueID::LibwebPaletteBase:
    case ValueID::LibwebPaletteBaseText:
    case ValueID::LibwebPaletteButton:
    case ValueID::LibwebPaletteButtonText:
    case ValueID::LibwebPaletteDesktopBackground:
    case ValueID::LibwebPaletteFocusOutline:
    case ValueID::LibwebPaletteHighlightWindowBorder1:
    case ValueID::LibwebPaletteHighlightWindowBorder2:
    case ValueID::LibwebPaletteHighlightWindowTitle:
    case ValueID::LibwebPaletteHoverHighlight:
    case ValueID::LibwebPaletteInactiveSelection:
    case ValueID::LibwebPaletteInactiveSelectionText:
    case ValueID::LibwebPaletteInactiveWindowBorder1:
    case ValueID::LibwebPaletteInactiveWindowBorder2:
    case ValueID::LibwebPaletteInactiveWindowTitle:
    case ValueID::LibwebPaletteLink:
    case ValueID::LibwebPaletteMenuBase:
    case ValueID::LibwebPaletteMenuBaseText:
    case ValueID::LibwebPaletteMenuSelection:
    case ValueID::LibwebPaletteMenuSelectionText:
    case ValueID::LibwebPaletteMenuStripe:
    case ValueID::LibwebPaletteMovingWindowBorder1:
    case ValueID::LibwebPaletteMovingWindowBorder2:
    case ValueID::LibwebPaletteMovingWindowTitle:
    case ValueID::LibwebPaletteRubberBandBorder:
    case ValueID::LibwebPaletteRubberBandFill:
    case ValueID::LibwebPaletteRuler:
    case ValueID::LibwebPaletteRulerActiveText:
    case ValueID::LibwebPaletteRulerBorder:
    case ValueID::LibwebPaletteRulerInactiveText:
    case ValueID::LibwebPaletteSelection:
    case ValueID::LibwebPaletteSelectionText:
    case ValueID::LibwebPaletteSyntaxComment:
    case ValueID::LibwebPaletteSyntaxControlKeyword:
    case ValueID::LibwebPaletteSyntaxIdentifier:
    case ValueID::LibwebPaletteSyntaxKeyword:
    case ValueID::LibwebPaletteSyntaxNumber:
    case ValueID::LibwebPaletteSyntaxOperator:
    case ValueID::LibwebPaletteSyntaxPreprocessorStatement:
    case ValueID::LibwebPaletteSyntaxPreprocessorValue:
    case ValueID::LibwebPaletteSyntaxPunctuation:
    case ValueID::LibwebPaletteSyntaxString:
    case ValueID::LibwebPaletteSyntaxType:
    case ValueID::LibwebPaletteTextCursor:
    case ValueID::LibwebPaletteThreedHighlight:
    case ValueID::LibwebPaletteThreedShadow1:
    case ValueID::LibwebPaletteThreedShadow2:
    case ValueID::LibwebPaletteVisitedLink:
    case ValueID::LibwebPaletteWindow:
    case ValueID::LibwebPaletteWindowText:
        return true;
    default:
        return false;
    }
}

Color IdentifierStyleValue::to_color(Optional<Layout::NodeWithStyle const&> node) const
{
    if (id() == CSS::ValueID::Currentcolor) {
        if (!node.has_value() || !node->has_style())
            return Color::Black;
        return node->computed_values().color();
    }

    if (!node.has_value()) {
        // FIXME: Can't resolve palette colors without layout node.
        return Color::Black;
    }

    auto& document = node->document();
    if (id() == CSS::ValueID::LibwebLink)
        return document.link_color();

    if (!document.page())
        return {};

    auto palette = document.page()->palette();
    switch (id()) {
    case CSS::ValueID::LibwebPaletteDesktopBackground:
        return palette.color(ColorRole::DesktopBackground);
    case CSS::ValueID::LibwebPaletteActiveWindowBorder1:
        return palette.color(ColorRole::ActiveWindowBorder1);
    case CSS::ValueID::LibwebPaletteActiveWindowBorder2:
        return palette.color(ColorRole::ActiveWindowBorder2);
    case CSS::ValueID::LibwebPaletteActiveWindowTitle:
        return palette.color(ColorRole::ActiveWindowTitle);
    case CSS::ValueID::LibwebPaletteInactiveWindowBorder1:
        return palette.color(ColorRole::InactiveWindowBorder1);
    case CSS::ValueID::LibwebPaletteInactiveWindowBorder2:
        return palette.color(ColorRole::InactiveWindowBorder2);
    case CSS::ValueID::LibwebPaletteInactiveWindowTitle:
        return palette.color(ColorRole::InactiveWindowTitle);
    case CSS::ValueID::LibwebPaletteMovingWindowBorder1:
        return palette.color(ColorRole::MovingWindowBorder1);
    case CSS::ValueID::LibwebPaletteMovingWindowBorder2:
        return palette.color(ColorRole::MovingWindowBorder2);
    case CSS::ValueID::LibwebPaletteMovingWindowTitle:
        return palette.color(ColorRole::MovingWindowTitle);
    case CSS::ValueID::LibwebPaletteHighlightWindowBorder1:
        return palette.color(ColorRole::HighlightWindowBorder1);
    case CSS::ValueID::LibwebPaletteHighlightWindowBorder2:
        return palette.color(ColorRole::HighlightWindowBorder2);
    case CSS::ValueID::LibwebPaletteHighlightWindowTitle:
        return palette.color(ColorRole::HighlightWindowTitle);
    case CSS::ValueID::LibwebPaletteMenuStripe:
        return palette.color(ColorRole::MenuStripe);
    case CSS::ValueID::LibwebPaletteMenuBase:
        return palette.color(ColorRole::MenuBase);
    case CSS::ValueID::LibwebPaletteMenuBaseText:
        return palette.color(ColorRole::MenuBaseText);
    case CSS::ValueID::LibwebPaletteMenuSelection:
        return palette.color(ColorRole::MenuSelection);
    case CSS::ValueID::LibwebPaletteMenuSelectionText:
        return palette.color(ColorRole::MenuSelectionText);
    case CSS::ValueID::LibwebPaletteWindow:
        return palette.color(ColorRole::Window);
    case CSS::ValueID::LibwebPaletteWindowText:
        return palette.color(ColorRole::WindowText);
    case CSS::ValueID::LibwebPaletteButton:
        return palette.color(ColorRole::Button);
    case CSS::ValueID::LibwebPaletteButtonText:
        return palette.color(ColorRole::ButtonText);
    case CSS::ValueID::LibwebPaletteBase:
        return palette.color(ColorRole::Base);
    case CSS::ValueID::LibwebPaletteBaseText:
        return palette.color(ColorRole::BaseText);
    case CSS::ValueID::LibwebPaletteThreedHighlight:
        return palette.color(ColorRole::ThreedHighlight);
    case CSS::ValueID::LibwebPaletteThreedShadow1:
        return palette.color(ColorRole::ThreedShadow1);
    case CSS::ValueID::LibwebPaletteThreedShadow2:
        return palette.color(ColorRole::ThreedShadow2);
    case CSS::ValueID::LibwebPaletteHoverHighlight:
        return palette.color(ColorRole::HoverHighlight);
    case CSS::ValueID::LibwebPaletteSelection:
        return palette.color(ColorRole::Selection);
    case CSS::ValueID::LibwebPaletteSelectionText:
        return palette.color(ColorRole::SelectionText);
    case CSS::ValueID::LibwebPaletteInactiveSelection:
        return palette.color(ColorRole::InactiveSelection);
    case CSS::ValueID::LibwebPaletteInactiveSelectionText:
        return palette.color(ColorRole::InactiveSelectionText);
    case CSS::ValueID::LibwebPaletteRubberBandFill:
        return palette.color(ColorRole::RubberBandFill);
    case CSS::ValueID::LibwebPaletteRubberBandBorder:
        return palette.color(ColorRole::RubberBandBorder);
    case CSS::ValueID::LibwebPaletteLink:
        return palette.color(ColorRole::Link);
    case CSS::ValueID::LibwebPaletteActiveLink:
        return palette.color(ColorRole::ActiveLink);
    case CSS::ValueID::LibwebPaletteVisitedLink:
        return palette.color(ColorRole::VisitedLink);
    case CSS::ValueID::LibwebPaletteRuler:
        return palette.color(ColorRole::Ruler);
    case CSS::ValueID::LibwebPaletteRulerBorder:
        return palette.color(ColorRole::RulerBorder);
    case CSS::ValueID::LibwebPaletteRulerActiveText:
        return palette.color(ColorRole::RulerActiveText);
    case CSS::ValueID::LibwebPaletteRulerInactiveText:
        return palette.color(ColorRole::RulerInactiveText);
    case CSS::ValueID::LibwebPaletteTextCursor:
        return palette.color(ColorRole::TextCursor);
    case CSS::ValueID::LibwebPaletteFocusOutline:
        return palette.color(ColorRole::FocusOutline);
    case CSS::ValueID::LibwebPaletteSyntaxComment:
        return palette.color(ColorRole::SyntaxComment);
    case CSS::ValueID::LibwebPaletteSyntaxNumber:
        return palette.color(ColorRole::SyntaxNumber);
    case CSS::ValueID::LibwebPaletteSyntaxString:
        return palette.color(ColorRole::SyntaxString);
    case CSS::ValueID::LibwebPaletteSyntaxType:
        return palette.color(ColorRole::SyntaxType);
    case CSS::ValueID::LibwebPaletteSyntaxPunctuation:
        return palette.color(ColorRole::SyntaxPunctuation);
    case CSS::ValueID::LibwebPaletteSyntaxOperator:
        return palette.color(ColorRole::SyntaxOperator);
    case CSS::ValueID::LibwebPaletteSyntaxKeyword:
        return palette.color(ColorRole::SyntaxKeyword);
    case CSS::ValueID::LibwebPaletteSyntaxControlKeyword:
        return palette.color(ColorRole::SyntaxControlKeyword);
    case CSS::ValueID::LibwebPaletteSyntaxIdentifier:
        return palette.color(ColorRole::SyntaxIdentifier);
    case CSS::ValueID::LibwebPaletteSyntaxPreprocessorStatement:
        return palette.color(ColorRole::SyntaxPreprocessorStatement);
    case CSS::ValueID::LibwebPaletteSyntaxPreprocessorValue:
        return palette.color(ColorRole::SyntaxPreprocessorValue);
    default:
        return {};
    }
}

}
