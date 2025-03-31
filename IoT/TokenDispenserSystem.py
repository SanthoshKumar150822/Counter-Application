import tkinter as tk
from tkinter import ttk, messagebox
import re
import time
from threading import Thread
import pywhatkit as kit

class WhatsAppTokenDispenser:
    def __init__(self, root):
        self.root = root
        self.root.title("WhatsApp Token Dispenser System")
        self.root.state('zoomed')  # Maximized window
        self.root.configure(bg="#f5f5f5")
        
        # Token counter
        self.token_counter = 0
        
        # Country data with codes and validation patterns
        self.country_data = [
            {"name": "Australia", "code": "+61", "pattern": r"^4\d{8}$"},
            {"name": "Brazil", "code": "+55", "pattern": r"^[1-9]{2}9?\d{8}$"},
            {"name": "Canada", "code": "+1", "pattern": r"^[2-9]\d{9}$"},
            {"name": "China", "code": "+86", "pattern": r"^1[3-9]\d{9}$"},
            
            {"name": "France", "code": "+33", "pattern": r"^[67]\d{8}$"},
            {"name": "Germany", "code": "+49", "pattern": r"^1[5-9]\d{8,9}$"},
            {"name": "India", "code": "+91", "pattern": r"^[6-9]\d{9}$"},
            {"name": "Japan", "code": "+81", "pattern": r"^[789]\d{8}$"},
            {"name": "Malaysia", "code": "+60", "pattern": r"^1[0-9]\d{7,8}$"},
            {"name": "Russia", "code": "+7", "pattern": r"^[3489]\d{9}$"},
            {"name": "Saudi Arabia", "code": "+966", "pattern": r"^5\d{8}$"},
            {"name": "Thailand", "code": "+66", "pattern": r"^[689]\d{8}$"},
            {"name": "UK", "code": "+44", "pattern": r"^7[1-9]\d{8}$"},
            {"name": "USA", "code": "+1", "pattern": r"^[2-9]\d{9}$"},
        ]
        
        self.create_ui()
    
    def create_ui(self):
        """Create the user interface"""
        # Main frame
        main_frame = tk.Frame(self.root, bg="#f5f5f5")
        main_frame.place(relx=0.5, rely=0.5, anchor="center")
        
        # Title
        title = tk.Label(
            main_frame,
            text="WhatsApp Token Dispenser System",
            font=("Helvetica", 20, "bold"),
            bg="#f5f5f5",
            fg="#2c3e50"
        )
        title.grid(row=0, column=0, columnspan=2, pady=(0, 30))
        
        # Country code label and dropdown
        country_label = tk.Label(
            main_frame,
            text="Country Code:",
            font=("Helvetica", 12),
            bg="#f5f5f5",
            fg="#34495e"
        )
        country_label.grid(row=1, column=0, sticky="e", padx=5, pady=5)
        
        self.country_var = tk.StringVar()
        country_codes = [f"{c['name']} ({c['code']})" for c in self.country_data]
        self.country_dropdown = ttk.Combobox(
            main_frame,
            textvariable=self.country_var,
            values=country_codes,
            state="readonly",
            font=("Helvetica", 12),
            width=20
        )
        self.country_dropdown.current(6)  # Default to India
        self.country_dropdown.grid(row=1, column=1, padx=5, pady=5)
        
        # Mobile number label and entry
        mobile_label = tk.Label(
            main_frame,
            text="Mobile Number:",
            font=("Helvetica", 12),
            bg="#f5f5f5",
            fg="#34495e"
        )
        mobile_label.grid(row=2, column=0, sticky="e", padx=5, pady=5)
        
        self.mobile_entry = tk.Entry(
            main_frame,
            font=("Helvetica", 12),
            width=25,
            bd=2,
            relief=tk.GROOVE
        )
        self.mobile_entry.grid(row=2, column=1, padx=5, pady=5)
        
        # Button frame
        button_frame = tk.Frame(main_frame, bg="#f5f5f5")
        button_frame.grid(row=3, column=0, columnspan=2, pady=20)
        
        # Generate Token button
        generate_btn = tk.Button(
            button_frame,
            text="Generate Token",
            font=("Helvetica", 12, "bold"),
            bg="#27ae60",
            fg="white",
            width=15,
            command=self.generate_token
        )
        generate_btn.pack(side=tk.LEFT, padx=10, ipady=5)
        
        # Reset button
        reset_btn = tk.Button(
            button_frame,
            text="Reset",
            font=("Helvetica", 12, "bold"),
            bg="#e74c3c",
            fg="white",
            width=15,
            command=self.reset_fields
        )
        reset_btn.pack(side=tk.LEFT, padx=10, ipady=5)
        
        # Style configuration
        self.style = ttk.Style()
        self.style.configure('TCombobox', padding=5, relief=tk.GROOVE)
        
        # Button styling
        for btn in [generate_btn, reset_btn]:
            btn.config(
                borderwidth=0,
                highlightthickness=0,
                relief=tk.FLAT,
                activebackground=btn.cget("bg"),
                activeforeground=btn.cget("fg")
            )
            btn.bind("<Enter>", lambda e, b=btn: b.config(bg=b.cget("activebackground")))
            btn.bind("<Leave>", lambda e, b=btn: b.config(bg="#27ae60" if b.cget("text") == "Generate Token" else "#e74c3c"))
    
    def generate_token(self):
        """Generate and send token via WhatsApp"""
        def task():
            country_info = self.country_dropdown.get()
            mobile_number = self.mobile_entry.get()
            
            if not country_info:
                messagebox.showerror("Error", "Please select a country")
                return
            
            if not mobile_number:
                messagebox.showerror("Error", "Please enter mobile number")
                return
            
            # Extract country code and name
            country_name = country_info.split(" (")[0]
            country_code = next((c["code"] for c in self.country_data if c["name"] == country_name), None)
            country_pattern = next((c["pattern"] for c in self.country_data if c["name"] == country_name), None)
            
            # Validate mobile number
            cleaned_number = re.sub(r'[^0-9]', '', mobile_number)
            if not re.match(country_pattern, cleaned_number):
                messagebox.showerror("Error", f"Invalid {country_name} mobile number format")
                return
            
            # Increment token counter
            self.token_counter += 1
            
            # Show confirmation message for 3 seconds
            self.show_confirmation(f"{country_code}{cleaned_number}", self.token_counter)
            
            # Wait for 3 seconds to show confirmation
            #time.sleep(3)
            
            # Send the message using pywhatkit
            try:
                phone_number = f"{country_code}{cleaned_number}"
                message = f"CSK Bank\nToken number: {self.token_counter}\nHave a nice day 😊"
                kit.sendwhatmsg(phone_number, message, time.localtime().tm_hour, time.localtime().tm_min + 1)  # Schedule message to send 1 minute later
                
                # Clear the fields after sending the message
                self.reset_fields()

            except Exception as e:
                messagebox.showerror("Error", f"Failed to send WhatsApp message: {str(e)}")

        # Run the task in a separate thread to keep the UI responsive
        thread = Thread(target=task)
        thread.start()

    def show_confirmation(self, phone_number, token):
        """Show confirmation screen"""
        self.confirmation_label = tk.Label(
            self.root,
            text=f"✓ Token Generated\nToken #{token} sent to: {phone_number}",
            font=("Helvetica", 14, "bold"),
            fg="#27ae60",
            bg="#f5f5f5"
        )
        self.confirmation_label.place(relx=0.5, rely=0.7, anchor="center")
        
    def reset_fields(self):
        """Reset all input fields"""
        self.country_dropdown.current(6)  # Reset to India
        self.mobile_entry.delete(0, tk.END)
        # Remove the confirmation message after resetting
        if hasattr(self, 'confirmation_label'):
            self.confirmation_label.destroy()

if __name__ == "__main__":
    root = tk.Tk()
    app = WhatsAppTokenDispenser(root)
    root.mainloop()
