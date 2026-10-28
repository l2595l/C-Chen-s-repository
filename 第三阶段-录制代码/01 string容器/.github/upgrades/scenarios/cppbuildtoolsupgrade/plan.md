# C++ Build Tools Upgrade Plan

## Overview

Target: 修复因 C++/MSVC 生成工具升级导致的生成中断问题（链接器多重定义错误）。
Scope: 1 个解决方案（D:\IT_Program\Data\第三阶段-录制代码\01 string容器\01 string容器.sln），重点定位并修复导致 LNK2005 / LNK1169 的重复定义问题，调整 .vcxproj/链接设置或代码以消除重复符号。

## Tasks

### 01-analyze-duplicate-main: 分析重复的 _main 符号

描述：使用完整重建报告中给出的路径，定位引发 LNK2005/LNK1169 的源文件与项目设置。阅读受影响的 .vcxproj 与源文件，列出所有可能导致重复 main 的原因（例如：误编译多个源文件为可执行、错误的项目类型、误添加生成单元等）。

Done when:
- 已识别产生重复定义的确切源文件或项目设置（使用工具输出的完整路径）。
- 形成明确的修复选项（修改源文件、调整项目设置或改变链接器输入）供用户选择或自动应用。

---

### 02-edit-project-or-source: 变更项目或源文件以消除重复定义（按需要）

描述：根据分析结果，执行必要更改。若需修改 .vcxproj，先卸载项目（按流程要求），编辑 .vcxproj，使用 `cppupgrade_validate_vcxproj_file` 验证，然后重新加载项目。若需修改源文件，确保语法与语义正确并包含必要的头文件/前置声明。

Done when:
- 源/项目修改已应用，且项目可重新加载（若修改了 .vcxproj，则已验证并重新加载）。
- 修改后的代码在增量构建中未引入新的错误（见下个任务的验证）。

---

### 03-incremental-build-and-fix: 增量构建并解决剩余问题

描述：使用 `cppupgrade_build_and_get_issues` 进行增量构建，按构建顺序逐个修复剩余错误/紧随其后的警告，直到当前修改的项目在增量构建中无错误。

Done when:
- 增量构建在受影响项目上无错误，或已记录无法自动修复的问题并回退到 Planning。

---

### 04-final-rebuild-validation: 最终完整重建与确认

描述：运行 `cppupgrade_rebuild_and_get_issues` 做一次完整重建，确认所有在-scope 的问题均已解决且未引入新的 out-of-scope 回归。

Done when:
- 完整重建报告显示 in-scope 问题已解决。
- 未引入新的 out-of-scope 回归；若出现回归，回到 Planning 重新评估。


