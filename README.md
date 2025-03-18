# Counter-Application
This application simulates a token-based queue management system for multiple service counters (e.g., bank counters, ticket counters, etc.). Users can generate tokens from token dispenser, and each token is assigned to a specific counter based on the counter operators call after an user gets token from token dispenser. The system ensures that tokens are assigned sequentially and that no two or more counters have the same token number at the same time. The application is designed to manage and display the current token number being served at each counter.

Key Features:
Token Generation: Users can generate tokens sequentially from the token dispenser
Counter Assignment: Tokens are assigned to any one of the four counters based on window operator's call.
Real-Time Updates: The system displays the current token number being served at each counter.
Error Handling: Invalid user inputs are handled gracefully.

Applications of This System:
Bank Counters: Managing customer queues for tellers or customer service representatives.
Ticket Counters: Assigning tokens for ticket purchases or inquiries at train stations, cinemas, or events.
Hospital Queues: Managing patient queues for different departments or doctors.
Government Offices: Handling queues for services like license renewals, document processing, etc.
Retail Stores: Managing customer queues for billing or service counters.
Call Centers: Assigning tokens to customers waiting for assistance.

Input range is 1 to 5
Input 1 to 4 is Window operator's call and 5 is user getting token from token dispenser.
