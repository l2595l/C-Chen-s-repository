# 03-incremental-build-and-fix: 增量构建并解决剩余问题

描述：使用 `cppupgrade_build_and_get_issues` 进行增量构建，按构建顺序逐个修复剩余错误/紧随其后的警告，直到当前修改的项目在增量构建中无错误。

Done when:
- 增量构建在受影响项目上无错误，或已记录无法自动修复的问题并回退到 Planning。

