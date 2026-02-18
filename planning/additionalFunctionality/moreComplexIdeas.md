# Conceptual Brainstorming: Advanced Features

---
**Authors:** Ali Alfridawi & Gemini (AI Assistant)  
**Purpose:** Document advanced feature ideas and complex system expansions to guide the long-term evolution of the Clarity project beyond its initial MVP.
---

1. Data Export (Reporting)	Export inventory logs to a timestamped .csv file for Excel compatibility.	
File I/O: Requires mastering fopen, fprintf, and managing file permissions/paths strings manually.	3/10 (Low)
2. Role-Based Access Control (RBAC)	Different menus for "Admins" (can delete users/items) vs. "Staff" (can only update stock).	
Logic State: You must carry a UserRole enum throughout the entire session lifecycle and wrap sensitive functions in if (user.role != ADMIN) return;.	4/10 (Low-Mid)
3. Password Hashing	Storing SHA-256 hashes instead of plain text passwords.	
External Libs: Requires linking an external library (like OpenSSL) or implementing a hashing algorithm manually (math-heavy).	6/10 (Mid)
4. Transactional Integrity	Ensure that if a "Recipe" deduction fails halfway (e.g., out of buns), the whole operation rolls back.	SQL Logic: Requires disabling AUTOCOMMIT in MySQL and manually handling COMMIT and ROLLBACK signals in C code.	6/10 (Mid)
5. Fuzzy Search	User types "tomat" and gets "Tomato".	
Algorithms: Requires implementing the Levenshtein Distance algorithm (string manipulation) to calculate similarity scores.	7/10 (High)
6. Undo / Redo System	Allow admins to "Undo" the last stock change.	
Data Structures: Requires implementing a Stack (Linked List) to store previous states of the database or specific actions.	8/10 (High)
7. Concurrency (Auto-Refresh)	The UI updates automatically if stock changes (without pressing a button).	
Threading: Requires pthreads. You must manage Mutex Locks to stop the drawing thread from reading while the DB thread is writing.	9/10 (Very High)
8. Networked Client/Server	Split the program: One "Server" executable runs the DB, and multiple "Client" executables connect via TCP/IP.	
Sockets: Requires Unix Sockets logic (sys/socket.h), packet serialization, and handling multiple connections simultaneously.	10/10 (Expert)
