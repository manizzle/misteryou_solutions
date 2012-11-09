;; Scheme functions for using Crank

;; Displays information about a componant
(define (display-componant-info c)
  (begin
    (display "Filename:             ")
    (display (componant-filename-get c)) (newline)
    (display "Name:                 ")
    (display (componant-type-lookup (componant-type-get c)))
    (display "_")
    (display (componant-name-get c)) (newline)
    (display "Description:          ")
    (display (componant-description-get c)) (newline)
    (display "Number of parameters: ")
    (display (componant-number-of-parameters-get c)) (newline)))

;; Runs the GUI neatly
(define (run-gui)
  (begin
    (display "Building crank gui") (newline)
    (start-gui)
    (display "Entering gui mainloop") (newline)
    (enter-gui)
    (display "Cleaning up...") (newline)
    (post-cleanup-gui)))

(define test-text "The quick brown fox jumps over the lazy dog.")

(define (current-patch name description)
  (generate-patch (get-current-transform) (get-current-heuristic) (get-current-fitness)
		  (get-current-gui-transform) (get-current-gui-heuristic) (get-current-gui-fitness)
		  name description))

 