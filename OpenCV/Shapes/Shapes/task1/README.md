1. Создан проект c++, подключена библиотека opencv, написана и проверена программа.
2. Для изменения цвета текста, редактируется параметр <b>Scalar color(255, 192, 203)</b>.
3. Для изменения шрифта текста, редактируется параметр int fontFace.  FONT_HERSHEY_SCRIPT_SIMPLEX >>> FONT_HERSHEY_TRIPLEX;
4. Для изменения самого текста, редактируется параметр putText();
5. Для изменения размеров окна, редактируются значения переменных  height, width, которые присваиваются параметру <b>Mat img(height, width, CV_8UC3);</b>
6. Для изменения положения текста, редактируется параметр Point textOrg, где 'параметр1' отвечает за отступ от левого края окна, а (img.rows / 'параметр2') это положение по вертикали, зависящий от параметр1.