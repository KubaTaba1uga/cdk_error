tests = [
  {'src': 'test_cdk_errno', 'c_args': ['-DCDK_ERROR_BTRACE_ENABLE=0']},
  {'src': 'test_cdk_errno', 'name': 'test_cdk_errno_with_backtrace'},
  {'src': 'test_cdk_errno_backtrace'},
  {'src': 'test_cdk_errno', 'name': 'test_cdk_errno_optimized', 'c_args': ['-DCDK_ERROR_OPTIMIZE']},
]

unity_subproject = subproject('unity')

unity_dependency = unity_subproject.get_variable('unity_dep')

test_runner = unity_subproject.get_variable('gen_test_runner')

subdir('test_unity.d')

foreach test : tests
  src = test['src']
  extra_c_args = test.has_key('c_args') ? test['c_args'] : []
  name = test.has_key('name') ? test['name'] : src

  exe = executable(name,
    sources: [src + '.c', test_runner.process(src + '.c')],
    dependencies: unity_dependency,
    include_directories: public_headers,
    c_args: extra_c_args,
  )

  test(name, exe)
endforeach
