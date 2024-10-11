file(REMOVE_RECURSE
  "libcore.a"
  "libcore.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/core.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
