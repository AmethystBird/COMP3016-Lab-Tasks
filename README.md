# COMP1004-Lab-Tasks
## Overview
All tasks follow in relation to the last task. For this reason, it is recommended that one completes each task linearly & does not skip any particular task.
## Index
[Week 5 - UML Diagrams](#uml-diagrams)
[Week 6 - HTML](#html)
[Week 7 - CSS](#css)
[Week 8 - JavaScript](#javascript)
## UML Diagrams
### Task 1 - Class
Create a class diagram depicting the following classes: MythicalAnimal, Dragon, Unicorn & Mermaid. Ensure that all classes have relevant attributes & functions. The relation between these classes (how they fit into the class hierarchy) must also be represented.
[Example Class Diagram](https://www.geeksforgeeks.org/unified-modeling-language-uml-class-diagrams/)
### Task 2 - State Machine
Create a state machine diagram depicting the high level behaviour of a microwave. Ensure that the microwave’s various states & the appropriate conditions for them to be met are represented.
[Example State Machine Diagram](https://sparxsystems.com/resources/tutorials/uml2/state-diagram.html)
### Task 3 - Activity
Create an activity diagram depicting the workflow of an individual cooking a meal (of any particular type). Consider where the individual might have multiple choices in how to cook this meal, as well as how they might have to reiterate over certain aspects & how they may require concurrent tasks to reduce the time required.
[Example Activity Diagram](https://en.wikipedia.org/wiki/Activity_diagram)
## HTML
### Task 4 - Development Tools
#### Integrated Development Environments (IDEs)
Use either notepad, notepad++, Visual Studio Code or Visual Studio.
#### Git & GitHub
[Install Git](https://git-scm.com/)
[Create a GitHub Account](https://github.com/)
[Install GitHub Desktop](https://desktop.github.com/download/)
#### Git Command Line
If desired, one may use Git through the command line as opposed to through the GUI provided by GitHub desktop. In the long-term, versatility with using Git through the command line is beneficial for more complex situations.
| Command | Description |
|--|--|
| git --version | Displays git version |
| git init | Initialises empty repository |
| git status | Displays files that are members of the repository of a particular directory |
| git add | Adds a file to a repository |
| git add --all | Adds all files in a directory to a repository |
| git commit -m "description" | Creates a 'save point' with respect to all files added |
| git push master/origin | Pushes commit to the master branch of the tracked repository |
| git fetch master/origin | Acquires most recent iteration of the master branch of the tracked repository & applies to the local repository |
### Task 5 - Site Creation
Create a site with a page title, a heading & a paragraph about any particular topic. On this site, include at least one hyperlink to another site & at least one image. Also ensure that you set defined width & height values for any included images if appropriate.
### Task 6 - Features
On the site from task 5, add a favicon & add at least one hyperlinked button in place of existing hyperlinked text where deemed appropriate. Also apply styling (through HTML; not CSS) to any elements where you deem appropriate. This can include but is not limited to text colour, font, background colour & blockquotes.
### Task 7 - Div Tag
On the site from task 6, add `<div>` tags to compartmentalise information where appropriate. To facilitate this, add at least one table element & one list element containing extra information in respect to the chosen topic.
## CSS
### Task 8 - Selection
On the site from task 7 (last week), remove all existing styling. Next, use a combination of both the CSS universal, grouping, class, element & ID selector systems where appropriate to stylise the site in the same spirit as prior. To clarify, you do not have to use all of them.
| Selector | Purpose |
|--|--|
| Universal | Stylises all elements |
| Grouping | Stylises a group of elements |
| Element | Stylises an element type |
| Class | Stylises a specific element by referencing its class attribute |
| ID | Stylises a specific element by referencing the element ID |
### Task 9 - External Files
On the site from task 8, transfer all the internal CSS into an external CSS file. Link the CSS file to the HTML file to continue referring to the CSS as before.
### Task 10 - Styling
On the site from task 9, replace the background colour with a background image. Modify the background repeat, position & attachment properties where appropriate. After this, apply any more styling at your own liberty if desired.
| Property | Purpose |
|--|--|
| Repeat | Whether to or & how to apply repetition to the display of an image |
| Position | The location of an image's anchor |
| Attachment | Whether or not an image moves in relation to scrolling |
## JavaScript
### Task 11 - Visibility Toggling
On the site from task 10, implement the ability for the user to reveal & hide elements using JavaScript statements & functions.
### Task 12 - External Files
On the site from task 11, transfer all the internal JavaScript into an external JavaScript file. Link the JavaScript file to the HTML file to continue referring to the JavaScript as before.
### Task 13 - Light & Dark Toggling
On the site from task 12, implement the ability for the user to switch between the existing site’s display mode to a dark mode equivalent (or a light mode, provided that the page is already dark) using JavaScript and additional CSS styling. The ability to toggle between modes could be facilitated through the use of a button with a JavaScript toggling function.
