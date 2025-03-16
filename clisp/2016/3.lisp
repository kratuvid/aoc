(progn

  (defun greater? (sides)
	(> (+ (first sides) (second sides)) (third sides)))

  (defun triangle? (sides)
	(and (greater? (list (first sides)  (second sides) (third sides)))
		 (greater? (list (first sides)  (third sides)  (second sides)))
		 (greater? (list (second sides) (third sides)  (first sides)))))

  (let ((valid-count 0))
	(dolist (line (uiop:read-file-lines "../../inputs/2016/3"))
	  (if (triangle? (mapcar #'parse-integer
								  (remove-if (lambda (s) (zerop (length s)))
											 (uiop:split-string line))))
		  (incf valid-count)))
	(format t "~%Found ~a valid triangles" valid-count))

  (let ((valid-count 0) (chunk '()))
	(dolist (line (uiop:read-file-lines "../../inputs/2016/3"))
	  (setq chunk (append chunk (list (mapcar #'parse-integer
											  (remove-if (lambda (s) (zerop (length s)))
														 (uiop:split-string line))))))
	  ;; (format t "~%~a: ~a" (length chunk) chunk)
	  (if (>= (length chunk) 3)
		  (progn
			(dotimes (col 3)
			  (if (triangle? (loop :for row :in chunk :collect (nth col row)))
				  (incf valid-count)))
			(setq chunk '()))))
	(format t "~%Using 2nd method, we found ~a valid triangles" valid-count))

  )
