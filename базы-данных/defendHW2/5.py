from tkinter import *
import sqlite3
con = sqlite3.connect('audio_collection.db')
cur = con.cursor()

data = [('1', 'track1', '2', '2000-12-12', '1', '1', '1'), ('2', 'track2', '2', '2000-12-12', '1', '1', '1'), ('3', 'track3', '2', '2000-12-12', '1', '1', '1'), ('4','track4', '2', '2000-12-12', '1', '1', '1')]

# cur.executemany("INSERT INTO audio_tracks VALUES(?, ?, ?, ?, ?, ?, ?);", data)

cur.execute("SELECT * FROM audio_tracks;")

def show_db():
    db = cur.fetchall()
    con.commit()
    text.delete("1.0","end")
    text.insert(INSERT, db)
    
def add_info():
    a1 = add_info1.get()
    a2 = add_info2.get()
    a3 = add_info3.get()
    a4 = add_info4.get()
    a5 = add_info5.get()
    a6 = add_info6.get()
    a7 = add_info7.get()

    add_mass =[(a1, a2, a3, a4, a5, a6, a7)]
    cur.executemany("INSERT INTO audio_tracks VALUES(?, ?, ?, ?, ?, ?, ?);", add_mass)
    cur.execute("SELECT * FROM audio_tracks;")
    con.commit()
    show_db()
    
def delete_by_id():
    id = int(delete_info.get())
    cur.execute("DELETE from audio_tracks WHERE id = ?", (id,))
    cur.execute("SELECT * FROM audio_tracks;")
    con.commit()
    show_db()
    
root = Tk()
root.title("Data Base")
root.geometry("800x250")
root['bg'] = 'grey'
root.resizable(width=False, height=False)

# Добавление информации
add_info1 = StringVar()
label1 = Label(text="ID", fg="white",  bg="grey")
label1.place(relx=0.1, rely=0)
add_var1 = Entry(textvariable=add_info1)
add_var1.place(relx=0.01, rely=0.07)

add_info2 = StringVar()
label2 = Label(text="Название", fg="white", bg="grey")
label2.place(relx=0.22, rely=0)
add_var2 = Entry(textvariable=add_info2)
add_var2.place(relx=0.15, rely=0.07)

add_info3 = StringVar()
label3 = Label(text="Длина", fg="white", bg="grey")
label3.place(relx=0.34, rely=0)
add_var3 = Entry(textvariable=add_info3)
add_var3.place(relx=0.29, rely=0.07)

add_info4 = StringVar()
label4 = Label(text="Дата выхода", fg="white", bg="grey")
label4.place(relx=0.46, rely=0)
add_var4 = Entry(textvariable=add_info4)
add_var4.place(relx=0.41, rely=0.07)

add_info5 = StringVar()
label5 = Label(text="Жанр ID", fg="white", bg="grey")
label5.place(relx=0.58, rely=0)
add_var5 = Entry(textvariable=add_info5)
add_var5.place(relx=0.53, rely=0.07)

add_info6 = StringVar()
label6 = Label(text="Тип ID", fg="white", bg="grey")
label6.place(relx=0.7, rely=0)
add_var6 = Entry(textvariable=add_info6)
add_var6.place(relx=0.65, rely=0.07)

add_info7 = StringVar()
label7 = Label(text="Альбом ID", fg="white", bg="grey")
label7.place(relx=0.82, rely=0)
add_var7 = Entry(textvariable=add_info7)
add_var7.place(relx=0.77, rely=0.07)

add_button = Button(text="Добавить", command=add_info)
add_button.place(relx=0.9, rely=0.07)

# Вывод информации
text = Text(width=70, height=4)
text.place(relx=0.01, rely=0.3)
look_button = Button(text="Вывести", command=show_db)
look_button.place(relx=0.5, rely=0.25)

# Удаление по ID
delete_info = StringVar()
delete_label = Label(text="Удалить по ID", fg="white", bg="grey")
delete_label.place(relx=0.01, rely=0.7)
delete_var = Entry(textvariable=delete_info)
delete_var.place(relx=0.12, rely=0.75)
delete_button = Button(text="Удалить", command=delete_by_id)
delete_button.place(relx=0.23, rely=0.75)

root.mainloop()
