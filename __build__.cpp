
#include <cppbuild.hpp>

int main(int argc, char* argv[])
{
    cppbuild::init(argc, argv);
    
    cppbuild::Target target("editor");

    target.folder(cppbuild::Folder("src")
            .files({
                "program.cpp",
            })
        );
        
    target.folder(cppbuild::Folder("libs")
            .folder(cppbuild::Folder("scintilla")
                .folder(cppbuild::Folder("src")
                    .files({
                        "AutoComplete.cxx",
                        "CallTip.cxx",
                        "CaseConvert.cxx",
                        "CaseFolder.cxx",
                        "CellBuffer.cxx",
                        "CharClassify.cxx",
                        "ContractionState.cxx",
                        "Decoration.cxx",
                        "Document.cxx",
                        "EditModel.cxx",
                        "Editor.cxx",
                        "EditView.cxx",
                        "Indicator.cxx",
                        "KeyMap.cxx",
                        "LineMarker.cxx",
                        "MarginView.cxx",
                        "PerLine.cxx",
                        "PositionCache.cxx",
                        "RESearch.cxx",
                        "RunStyles.cxx",
                        "Selection.cxx",
                        "Style.cxx",
                        "UniConversion.cxx",
                        "ViewStyle.cxx",
                        "XPM.cxx",
                        "ScintillaBase.cxx",
                    })
                )
                .folder(cppbuild::Folder("lexlib")
                    .files({
                        "CharacterCategory.cxx",
                        "CharacterSet.cxx",
                        "PropSetSimple.cxx",
                    })
                )
                .folder(cppbuild::Folder("win32")
                    .files({
                        "PlatWin.cxx",
                        "HanjaDic.cxx",
                        "ScintillaWin.cxx",
                    })
                )
            )
        );
    target.includeDirs({
        "libs\\scintilla\\include",
        "libs\\scintilla\\src",
        "libs\\scintilla\\lexlib",
    });

    target.libraries({
        "kernel32",
        "user32",
        "gdi32",
        "ole32",
        "oleaut32",
        "imm32",
        "uuid",
    });

    return 0;
}