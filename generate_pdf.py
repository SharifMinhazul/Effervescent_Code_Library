#!/usr/bin/python
import os
import subprocess
import argparse

code_dir = "code"

# Default values
DEFAULT_NAME = "SANJIDUR RAHMAN"
DEFAULT_ROLL = "2307006"

# Allowed source code extensions
ALLOWED_EXTENSIONS = {
    "c",
    "cc",
    "cpp",
    "h",
    "hpp",
    "cxx",  # C/C++
    "java",  # Java
    "py",  # Python
    "js",
    "ts",  # JavaScript/TypeScript
    "sh",
    "bash",  # Shell
    "txt",
    "md",  # Text
    "html",
    "css",  # Web
    "sql",  # SQL
    "json",
    "xml",
    "yaml",
    "yml",  # Config
    "rs",  # Rust
    "go",  # Go
    "rb",  # Ruby
    "php",  # PHP
    "kt",  # Kotlin
    "scala",  # Scala
    "hs",  # Haskell
}


def is_binary_file(filepath):
    """Check if a file is binary"""
    try:
        with open(filepath, "rb") as f:
            chunk = f.read(8192)
            # Check for null bytes (common in binary files)
            if b"\x00" in chunk:
                return True
            # Check for high ratio of non-text characters
            text_chars = bytearray(
                {7, 8, 9, 10, 12, 13, 27} | set(range(0x20, 0x100)) - {0x7F}
            )
            non_text = sum(1 for byte in chunk if byte not in text_chars)
            if len(chunk) > 0 and non_text / len(chunk) > 0.3:
                return True
        return False
    except Exception:
        return True


def is_valid_source_file(filepath):
    """Check if file is a valid source code file"""
    # Get extension
    ext = filepath.lower().split(".")[-1] if "." in filepath else ""

    # Check if extension is allowed
    if ext not in ALLOWED_EXTENSIONS:
        return False

    # Check if it's not a binary file
    if is_binary_file(filepath):
        return False

    return True


def count_lines(filepath):
    """Count lines in a file, handling different encodings"""
    encodings = ["utf-8", "latin-1", "cp1252", "iso-8859-1"]
    for encoding in encodings:
        try:
            with open(filepath, "r", encoding=encoding) as f:
                return len(f.readlines())
        except (UnicodeDecodeError, UnicodeError):
            continue
    # Fallback: count lines as binary
    try:
        with open(filepath, "rb") as f:
            return len(f.readlines())
    except Exception:
        return 0


def get_sections():
    sections = []
    for root, dirs, files in os.walk(code_dir):
        subsections = []
        section_name = os.path.basename(root)
        sections.append((section_name, subsections))
        for file_name in sorted(files):
            subsection_name = os.path.splitext(file_name)[0]

            # Skip hidden files
            if subsection_name.startswith("."):
                continue

            relative_path = os.path.join(root, file_name)

            # Skip binary and non-source files
            if not is_valid_source_file(relative_path):
                print(f"Skipping (binary/non-source): {file_name}")
                continue

            print(f"Processing: {file_name}")
            number_of_lines = count_lines(relative_path)
            try:
                hash_value = subprocess.check_output(
                    ["md5sum", relative_path], text=True
                ).split()[0][:8]
            except Exception:
                hash_value = "--------"
            subsections.append(
                (relative_path, subsection_name, number_of_lines, hash_value)
            )
    return sections[1:]


def get_style(filename):
    ext = filename.lower().split(".")[-1] if "." in filename else ""
    if ext in ["c", "cc", "cpp", "h", "hpp", "cxx"]:
        return "c++"
    elif ext in ["java"]:
        return "java"
    elif ext in ["py"]:
        return "python"
    elif ext in ["js"]:
        return "javascript"
    elif ext in ["ts"]:
        return "typescript"
    elif ext in ["sh", "bash"]:
        return "bash"
    elif ext in ["sql"]:
        return "sql"
    elif ext in ["html"]:
        return "html"
    elif ext in ["css"]:
        return "css"
    elif ext in ["json"]:
        return "json"
    elif ext in ["xml"]:
        return "xml"
    elif ext in ["yaml", "yml"]:
        return "yaml"
    elif ext in ["rs"]:
        return "rust"
    elif ext in ["go"]:
        return "go"
    elif ext in ["rb"]:
        return "ruby"
    elif ext in ["php"]:
        return "php"
    elif ext in ["kt"]:
        return "kotlin"
    elif ext in ["hs"]:
        return "haskell"
    else:
        return "text"


def texify(s):
    """Escape special LaTeX characters"""
    special_chars = {
        "&": r"\&",
        "%": r"\%",
        "$": r"\$",
        "#": r"\#",
        "_": r"\_",
        "{": r"\{",
        "}": r"\}",
        "~": r"\textasciitilde{}",
        "^": r"\textasciicircum{}",
    }
    for char, replacement in special_chars.items():
        s = s.replace(char, replacement)
    return s


def get_tex(sections):
    tex = ""
    for section_name, subsections in sections:
        if not subsections:  # Skip empty sections
            continue
        tex += "\\section{%s}\n" % texify(section_name)
        for relative_path, subsection_name, number_of_lines, hash_value in subsections:
            tex += "\\subsection{\\small %s  \\scriptsize [%s lines] - %s}\n" % (
                texify(subsection_name),
                number_of_lines,
                hash_value,
            )
            tex += "\\inputminted{%s}{%s}\n" % (get_style(relative_path), relative_path)
        tex += "\n"
    return tex


def update_notebook_tex(name, roll):
    """Update notebook.tex with the provided name and roll"""
    with open("notebook.tex", "r", encoding="utf-8") as f:
        content = f.read()

    import re

    content = re.sub(
        r"\\newcommand\{\\studentname\}\{.*?\}",
        f"\\\\newcommand{{\\\\studentname}}{{{name}}}",
        content,
    )
    content = re.sub(
        r"\\newcommand\{\\studentroll\}\{.*?\}",
        f"\\\\newcommand{{\\\\studentroll}}{{{roll}}}",
        content,
    )

    with open("notebook.tex", "w", encoding="utf-8") as f:
        f.write(content)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate DSA Lab Task PDF")
    parser.add_argument(
        "--name",
        "-n",
        default=DEFAULT_NAME,
        help=f"Student name (default: {DEFAULT_NAME})",
    )
    parser.add_argument(
        "--roll",
        "-r",
        default=DEFAULT_ROLL,
        help=f"Roll number (default: {DEFAULT_ROLL})",
    )
    args = parser.parse_args()

    print(f"Generating PDF for: {args.name} ({args.roll})")

    # Update notebook.tex with name and roll
    update_notebook_tex(args.name, args.roll)

    # Generate contents.tex
    sections = get_sections()
    tex = get_tex(sections)
    with open("contents.tex", "w", encoding="utf-8") as f:
        f.write(tex)

    print("\nGenerated contents.tex")

    # Compile LaTeX
    latexmk_options = ["latexmk", "-pdf", "-shell-escape", "-cd", "notebook.tex"]
    subprocess.call(latexmk_options)
