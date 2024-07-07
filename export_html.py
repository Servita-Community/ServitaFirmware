"""Script to export the the main.html to a .h file.

The exported .h files will contain string literals that can be used in the ino main file. This
allows modular development of the html files and local testing without the need to copy over or
maintain the html files separately.

html/main.html -> Servita/main_html.h
"""
import os

def main():
    html_path = os.path.join(os.path.dirname(__file__), 'html')
    main_html_path = os.path.join(html_path, 'main.html')
    main_mini_html_path = os.path.join(html_path, 'main_mini.html')
    servita_path = os.path.join(os.path.dirname(__file__), 'Servita')

    # Read the html files
    with open(main_html_path, 'r') as f:
        main_html = f.read()
    
    with open(main_mini_html_path, 'r') as f:
        main_mini_html = f.read()

    # Write the html files to the .h files
    with open(os.path.join(servita_path, 'inc/main_html.h'), 'w') as f:
        f.write('const char main_html[] PROGMEM = R"rawliteral(\n')
        f.write(main_html)
        f.write('\n)rawliteral\";')
    
    with open(os.path.join(servita_path, 'inc/main_mini_html.h'), 'w') as f:
        f.write('const char main_mini_html[] PROGMEM = R"rawliteral(\n')
        f.write(main_mini_html)
        f.write('\n)rawliteral\";')


if __name__ == '__main__':
    main()