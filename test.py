import os
import subprocess


def find_project_root(start_dir):
    """
    从 start_dir 开始，逐步回退查找包含 CMakeLists.txt 或 build 目录的项目根目录。
    """
    current_dir = start_dir
    while current_dir != "/":  # 回退直到根目录
        if os.path.exists(os.path.join(current_dir, 'CMakeLists.txt')) or \
                os.path.exists(os.path.join(current_dir, 'build')):
            return current_dir
        current_dir = os.path.dirname(current_dir)

    return None  # 如果没有找到合适的目录，返回 None


def find_executable(project_root, target_dir):
    """
    在项目根目录下的 build/bin 目录中寻找与 target_dir 对应的可执行文件。
    """
    # 计算相对路径，得到目标文件的相对位置
    relative_path = os.path.relpath(target_dir, project_root)

    # 拆分相对路径
    parts = relative_path.split(os.sep)

    # `file_name` 是路径的最后一个部分
    file_name = parts[-1]
    # `contest` 是倒数第二个部分
    contest = parts[-2]
    # `relative_path_head` 是路径的其余部分
    relative_path_head = os.sep.join(parts[:-2])

    # 构建新的文件名
    executable_name = f"{contest}_{file_name}"

    # 拼接新的相对路径
    new_relative_path = os.path.join(relative_path_head, contest,
                                     executable_name)

    # 构建 build/bin 下的路径
    executable = os.path.join(project_root, 'build', 'bin', new_relative_path)

    # 检查该路径是否是可执行文件
    if os.path.isfile(executable):
        return executable
    else:
        print(f"Error: {executable} is not a valid executable file")
        return None


def run_executable_on_test(executable, input_path, expected_output_path,
                           actual_output_path):
    """
    运行可执行文件，执行测试并将实际输出与期望输出进行比较。
    """
    # 运行可执行文件，并将输出写入实际输出文件
    with open(input_path, 'r') as infile, open(actual_output_path,
                                               'w') as outfile:
        subprocess.run([executable], stdin=infile, stdout=outfile,
                       stderr=subprocess.PIPE)

    # 比较实际输出与期望输出
    if os.path.exists(expected_output_path):
        with open(expected_output_path, 'r') as expected_file, open(
                actual_output_path, 'r') as actual_file:
            expected_output = expected_file.read().strip()
            actual_output = actual_file.read().strip()

            if expected_output == actual_output:
                print(f"Test {os.path.basename(input_path)}: PASSED")
            else:
                print(f"Test {os.path.basename(input_path)}: FAILED")
                print(f"Expected:\n{expected_output}")
                print(f"Got:\n{actual_output}")
    else:
        print(f"Warning: Expected output file not found for {input_path}")


def run_tests_on_directory(executable, test_dir):
    """
    遍历 test 目录，针对所有输入文件运行可执行文件，并执行测试。
    """
    for input_file in os.listdir(test_dir):
        if input_file.endswith('.in'):
            test_name = os.path.splitext(input_file)[0]
            input_path = os.path.join(test_dir, input_file)
            expected_output_path = os.path.join(test_dir, f"{test_name}.out")
            actual_output_path = os.path.join(test_dir,
                                              f"{test_name}_actual.out")

            # 运行可执行文件并执行测试
            run_executable_on_test(executable, input_path, expected_output_path,
                                   actual_output_path)


def run_tests(target_dir):
    """
    主函数，获取可执行文件，并运行测试。
    """
    test_dir = os.path.join(target_dir, 'test')

    # 确保 test 目录存在
    if not os.path.exists(test_dir):
        print(f"Error: 'test' directory does not exist in {target_dir}")
        return

    # 查找项目根目录
    project_root = find_project_root(target_dir)
    if project_root is None:
        print(f"Error: Could not find project root from {target_dir}")
        return

    # 在项目根目录下的 build/bin 目录中寻找可执行文件
    executable = find_executable(project_root, target_dir)
    if executable is None:
        print(f"Error: No executable file found for {target_dir}")
        return

    print(f"Running tests using executable: {executable}")

    # 执行测试
    run_tests_on_directory(executable, test_dir)


if __name__ == "__main__":
    import sys

    if len(sys.argv) != 2:
        print("Usage: python run_tests.py <directory>")
        sys.exit(1)

    directory = sys.argv[1]
    run_tests(directory)
